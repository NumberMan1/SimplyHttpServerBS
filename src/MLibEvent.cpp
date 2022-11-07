#include "MLibEvent.h"
#include <iostream>
#include <exception>
#include <vector>
#include "Log.h"

std::shared_ptr<MEvent::EventHandler> 
MEvent::EventHandler::mInstance = nullptr;

MEvent::EventHandler::EventHandler() noexcept
    : mSockAddrInPtr(std::make_unique<sockaddr_in>())
    , mBasePtr(nullptr, event_base_free)
    , mEventSignals()
    , mListenerPtr(nullptr, evconnlistener_free)
{
    mSockAddrInPtr->sin_family = AF_INET;
    mSockAddrInPtr->sin_port = htons(PORT);
    mSockAddrInPtr->sin_addr.s_addr = INADDR_ANY;
}

void MEvent::EventHandler::init(ListenerCallBack _cb) {
    auto base = event_base_new();
    if (!base) {
        LOG("不能创建event_base!");
        throw std::runtime_error("不能创建event_base!");
    }
    mBasePtr.reset(std::move(base));
    auto listener = 
        evconnlistener_new_bind(mBasePtr.get(), _cb, mBasePtr.get(),
                                LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
                                reinterpret_cast<sockaddr*>(mSockAddrInPtr.get()), 
                                sizeof(*mSockAddrInPtr));
    if (!listener) {
        LOG("不能创建evconnlistener!");
        throw std::runtime_error("不能创建evconnlistener!");
    }
    mListenerPtr.reset(std::move(listener));
}

std::shared_ptr<MEvent::EventHandler> 
MEvent::EventHandler::instance(ListenerCallBack _cb) {
    if (!mInstance) {
        mInstance = std::move(
            std::shared_ptr<EventHandler>(new EventHandler())
        );
        mInstance->init(_cb);
    }
    return mInstance;
}

MEvent::EventHandler::~EventHandler() noexcept {
    std::cout << "~EventHandler 调用" << std::endl;
    mInstance = nullptr;
    try {
        // if (event_base_got_exit(mBasePtr.get()))
            // this->exit();
    } catch (...) {
        LOG("unknow error");
    }
} 
 
// bool MEvent::EventHandler::delEvent(const int &_fd) noexcept {
//     if (mEvents.contains(_fd)) {
//         mEvents.erase(_fd);
//         return true;
//     } else {
//         return false;
//     }
// }

bool MEvent::EventHandler::delSignal(const int &_fd) noexcept {
    if (mEventSignals.contains(_fd)) {
        mEventSignals.erase(_fd);
        return true;
    } else {
        return false;
    }
}

void MEvent::EventHandler::dispatch() {
    event_base_dispatch(mBasePtr.get());
}

void MEvent::EventHandler::exit(const timeval * _timeout) {
    std::cout << "someone exit" << std::endl;
    event_base_loopexit(mBasePtr.get(), _timeout);
}

std::string_view MEvent::EventHandler::getBaseMethod() const {
    return event_base_get_method(mBasePtr.get());
}

// void MEvent::EventHandler::addEvent
// (SockFdType _fd, EventCallBack _cb, short _op, void *_arg, timeval *_timeout) {
//     event *ev = event_new(mBasePtr.get(), _fd, _op, _cb, _arg);
//     if (!ev || event_add(ev, _timeout) < 0) {
//         LOG("不能创建event! 或 event_add失败");
//         throw std::runtime_error("不能创建event! 或 event_add失败");
//     }
//     std::unique_ptr<event, decltype(event_free)*> ptr(std::move(ev), event_free);
//     mEvents.insert(std::make_pair<SockFdType, decltype(ptr)>(std::move(_fd), std::move(ptr)));
// }

void MEvent::EventHandler::addSignal
(evutil_socket_t _x, SignalCallBack _cb, void *_arg, timeval *_timeout) {
    auto signal = evsignal_new(mBasePtr.get(), _x, _cb, _arg);
    if (!signal || evsignal_add(signal, _timeout)) {
        LOG("创建evsignal失败");
        throw std::runtime_error("创建evsignal失败");
    }
    std::unique_ptr<SignalEvent, decltype(event_free)*> ptr(std::move(signal), event_free);
    mEventSignals.insert(std::make_pair<evutil_socket_t, decltype(ptr)>(std::move(_x), std::move(ptr)));
}