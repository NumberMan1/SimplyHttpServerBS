#include "MLibEvent.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include <iostream>

using namespace MEvent;

namespace {

void listenerCB(ConListener *_evl, SockFdType _fd,
                sockaddr *_cliaddr, int _socklen, void *_base);
void sigintCB(evutil_socket_t _x, short _events, void *_arg);
void bufEvCB(bufferevent *_buffEv, short _what, void *_ctx);
void bufReadCB(bufferevent *_buffEv, void *_ctx);
void bufWriteCB(bufferevent *_buffEv, void *_ctx);

} // !namespace

int main(int argc, char *argv[]) {
    timeval timeout { 5, 0 };
    EventHandler::instance(::listenerCB);
    EventHandler::mInstance->addSignal(SIGINT, ::sigintCB,
        EventHandler::mInstance->getBase(), &timeout
    );
    EventHandler::mInstance->dispatch();
    return 0;
}

namespace {

void listenerCB(ConListener *_evl, SockFdType _fd,
                sockaddr *_cliaddr, int _socklen, void *_base)
{
    Base *base = reinterpret_cast<Base*>(_base);
    auto buffEvPtr = 
        bufferevent_socket_new(base, _fd, BEV_OPT_CLOSE_ON_FREE);
    if (!buffEvPtr) {
        LOG("不能创建buffer_event");
        return;
    }
    bufferevent_setcb(buffEvPtr, ::bufReadCB, ::bufWriteCB, ::bufEvCB, nullptr);
    bufferevent_enable(buffEvPtr, EV_WRITE);
    bufferevent_enable(buffEvPtr, EV_READ);
}

void sigintCB(evutil_socket_t _x, short _events, void *_arg) {
    Base *base = reinterpret_cast<event_base*>(_arg);
	timeval delay = { 2, 0 };
	std::cout << "Caught an interrupt signal;"
              << " exiting cleanly in two seconds." << std::endl;
	event_base_loopexit(base, &delay);
}

void bufEvCB(bufferevent *_buffEv, short _what, void *_ctx) {

}

void bufReadCB(bufferevent *_buffEv, void *_ctx) {

}

void bufWriteCB(bufferevent *_buffEv, void *_ctx) {

}

} // !namespace