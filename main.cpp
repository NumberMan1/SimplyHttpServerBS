#include <sys/types.h>
#include <sys/stat.h>
// #include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>

#include <iostream>
#include <cstring>
#include <filesystem>

#include "MLibEvent.h"
#include "Pub.h"
#include "WebOp.h"

using namespace MEvent;

namespace {

// LibEvent的回调函数
void listenerCB(ConListener *_evl, SockFdType _fd,
                sockaddr *_cliaddr, int _socklen, void *_base);
void sigintCB(evutil_socket_t _x, short _events, void *_arg);
void bufReadCB(bufferevent *_buffEv, void *_arg);
void bufWriteCB(bufferevent *_buffEv, void *_arg);
void http_request(bufferevent *_buffEv, char *_path);
bool sendDir(bufferevent *_buffEv, const char *_strPath);

} // !namespace

int main(int argc, char *argv[]) {
    struct sigaction s;
    s.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &s, nullptr);
	//改变当前进程的工作目录
    // old style

    // char path[255] = {0};
    // std::ignore = sprintf(path, "%s", getenv("PWD"));
    // std::ignore = strcat(path, "/webpath");
    // std::ignore = chdir(path);
    // std::cout << "当前工作目录为" << path << std::endl;

    // C++17 style

    std::filesystem::path path = std::filesystem::current_path();
    std::cout << "以前工作目录为" << path << std::endl;
    path.append("webpath");
    std::filesystem::current_path(path);
    std::cout << std::filesystem::current_path() << std::endl;

    std::ignore = EventHandler::instance(::listenerCB);
    EventHandler::mInstance->addSignal(SIGINT, ::sigintCB,
        EventHandler::mInstance->getBase(), nullptr
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
    bufferevent_setcb(buffEvPtr, ::bufReadCB, ::bufWriteCB, Web::evHandle, nullptr);
    std::ignore = bufferevent_enable(buffEvPtr, EV_WRITE);
    std::ignore = bufferevent_enable(buffEvPtr, EV_READ);
}

void sigintCB(evutil_socket_t _x, short _events, void *_arg) {
    Base *base = reinterpret_cast<event_base*>(_arg);
	timeval delay = { 2, 0 };
	std::cout << "Caught an interrupt signal;"
              << " exiting cleanly in two seconds." << std::endl;
	if(event_base_loopexit(base, &delay) < 0) {
        throw std::runtime_error("event_base_loopexit 调用失败");
    }
}

bool sendDir(bufferevent *_buffEv, const char *_strPath) {
    Web::sendFile(_buffEv, "html/dir_header.html");
    dirent **dirPPtr = nullptr;
    // 用dirPPtr申请dir的空间
    int dirNum = scandir(_strPath, &dirPPtr, nullptr, alphasort);
    if (dirNum < 0) {
        LOG("访问目录出错");
        return false;
    }
    for (int i = 0; i != dirNum; ++i) {
        std::cout << dirPPtr[i]->d_name << std::endl;
        int len;
        char files[1024]{0};
        if (dirPPtr[i]->d_type == DT_DIR) { // 如果是目录需要加/
            len = sprintf(files, "<li><a href=\"%s/\"> %s </a></li>",
                          dirPPtr[i]->d_name, dirPPtr[i]->d_name);
        } else {
            len = sprintf(files, "<li><a href=\"%s\"> %s </a></li>",
                          dirPPtr[i]->d_name, dirPPtr[i]->d_name);
        }
        // 记得free 空间
        free(dirPPtr[i]);
        if (bufferevent_write(_buffEv, files, len) == -1) {
            bufferevent_free(_buffEv);
        }
    }
    Web::sendFile(_buffEv, "html/dir_tail.html");
    return true;
}

bool httpRequest(bufferevent *_buffEv, char *_path) {
    const char *strFile = _path;
    if(strcmp(strFile, "/") == 0 ||
       strcmp(strFile, "/.") == 0) {
        strFile = "./"; // 如果访问的是默认目录的话
    } else {
        strFile = _path + 1; // 忽略文件名的第一个/
    }
    struct stat st;
    if (stat(strFile, &st) < 0) { // 文件不存在
        LOG("文件不存在或用户离开");
        Web::sendMsg(_buffEv, 404, "NOT FOUND", get_mime_type(".html"), 0);
        Web::sendFile(_buffEv, "html/error.html");
        return false;
    } else {
        if (S_ISREG(st.st_mode)) { // 为普通文件
            std::cout << "请求普通文件中" << std::endl;
            Web::sendMsg(_buffEv, 200, "OK", get_mime_type(strFile), st.st_size);
            Web::sendFile(_buffEv, strFile);
        } else if (S_ISDIR(st.st_mode)) { // 访问目录
            std::cout << "访问目录文件" << std::endl;
            Web::sendMsg(_buffEv, 200, "OK", get_mime_type(".html"), st.st_size);
            sendDir(_buffEv, strFile);
        }
    }
    return true;
}

void bufReadCB(bufferevent *_buffEv, void *_arg) {
    char buf[1024] {0};
    int check = bufferevent_read(_buffEv,
         reinterpret_cast<void*>(buf), sizeof(buf)
    );
    if (check > 0) {
        char reqType[10] {0}; // GET
        char fileName[256] {0}; // /a.text
        char protocal[20] {0}; // HTTP/1.1
    	std::ignore = sscanf(buf, "%[^ ] %[^ ] %[^ \r\n]", reqType, fileName, protocal);
        strdecode(fileName, fileName);
        if (strcasecmp(reqType, "get") == 0) {
            while(bufferevent_read(_buffEv, buf, sizeof(buf)) > 0){
                std::cout << buf << std::endl;
            }
            httpRequest(_buffEv, fileName);
        }
    }
}

void bufWriteCB(bufferevent *_buffEv, void *_arg) {

}


} // !namespace
