#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>

#include <iostream>
#include <cstring>

#include "MLibEvent.h"
#include "Pub.h"
#include "WebOp.h"

using namespace MEvent;

namespace {

// LibEvent的回调函数
void listenerCB(ConListener *_evl, SockFdType _fd,
                sockaddr *_cliaddr, int _socklen, void *_base);
void sigintCB(evutil_socket_t _x, short _events, void *_arg);
void bufEvCB(bufferevent *_buffEv, short _what, void *_ctx);
void bufReadCB(bufferevent *_buffEv, void *_ctx);
void bufWriteCB(bufferevent *_buffEv, void *_ctx);

// 自定义发送数据函数
// void sendMsg(bufferevent *_buffEv, const int &_code,
//              const char *_info, const char *_filetype,
//              const int &_len);
// void sendFile(bufferevent *_buffEv, const char* _fileName);

} // !namespace

int main(int argc, char *argv[]) {
	//改变当前进程的工作目录
    char path[255] = {0};
    std::ignore = sprintf(path, "%s", getenv("PWD"));
    std::ignore = strcat(path, "/webpath");
    std::ignore = chdir(path);
    std::cout << "当前工作目录为" << path << std::endl;
    // timeval timeout { 5, 0 };
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
    bufferevent_setcb(buffEvPtr, ::bufReadCB, ::bufWriteCB, ::bufEvCB, nullptr);
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

void bufEvCB(bufferevent *_buffEv, short _what, void *_ctx) {

}

void bufReadCB(bufferevent *_buffEv, void *_ctx) {
    char buf[1024] {0};
    std::ignore = bufferevent_read(_buffEv,
         reinterpret_cast<void*>(buf), sizeof(buf)
    );
    std::cout << buf << std::endl;
    char reqType[16] {0}; // GET
    char fileName[100] {0}; // /a.text
    char protocal[200] {0}; // HTTP/1.1
	std::ignore = sscanf(buf, "%[^ ] %[^ ] %[^ \r\n]", reqType, fileName, protocal);
    std::cout << reqType << '\n'
              << fileName << '\n'
              << protocal << std::endl;
    if (strcasecmp(reqType, "get") == 0) {
        char *strFile = fileName + 1; // 忽略文件名的第一个/
        if (*strFile == 0)  {// 没有请求默认当前目录 
        }
        struct stat st;
        if (stat(strFile, &st) < 0) { // 文件不存在
            std::cout << "文件不存在" << std::endl;
            Web::sendMsg(_buffEv, 404, "NOT FOUND", get_mime_type(".html"), 0);
            Web::sendFile(_buffEv, "html/error.html");
        } else {
            if (S_ISREG(st.st_mode)) { // 为普通文件
                std::cout << "请求普通文件中" << std::endl;
                Web::sendMsg(_buffEv, 200, "OK", get_mime_type(strFile), st.st_size);
                Web::sendFile(_buffEv, strFile);
            } else if (S_ISDIR(st.st_mode)) { // 访问目录
                std::cout << "访问目录文件" << std::endl;
                Web::sendMsg(_buffEv, 200, "OK", get_mime_type(".html"), st.st_size);
                Web::sendFile(_buffEv, "html/dir_header.html");

                dirent **dirPPtr = nullptr;
                // 用dirPPtr申请dir的空间
                int dirNum = scandir(strFile, &dirPPtr, nullptr, alphasort);
                for (int i = 0; i != dirNum; ++i) {
                    std::cout << dirPPtr[i]->d_name << std::endl;
                    char files[1024]{0};
                    int len = sprintf(files, "<li><a href=%s> %s </a></li>",
                                      dirPPtr[i]->d_name, dirPPtr[i]->d_name);
                    bufferevent_write(_buffEv, files, len);
                    // 记得free 空间
                    free(dirPPtr[i]);
                }
                Web::sendFile(_buffEv, "html/dir_tail.html");
            }
        }
    }
}

void bufWriteCB(bufferevent *_buffEv, void *_ctx) {

}

// void sendMsg(bufferevent *_buffEv, const int &_code,
//              const char *_info, const char *_filetype,
//              const int &_len)
// {
//     char sendBuff[1024] {0};
//     sprintf(sendBuff, "HTTP/1.1 %d %s\r\n", _code, _info);
//     sprintf(sendBuff + strlen(sendBuff),
//             "Content-Type:%s\r\n", _filetype);
//     if (_len > 0) {
//         sprintf(sendBuff + strlen(sendBuff),
//                 "Content-Length:%d\r\n", _len);
//     }
//     strcat(sendBuff, "\r\n");
//     std::cout << sendBuff << std::endl;
//     bufferevent_write(_buffEv, sendBuff, strlen(sendBuff));
// }

// void sendFile(bufferevent *_buffEv, const char *_fileName) {
//     std::cout << _fileName << std::endl;
//     int fileFD = open(_fileName, O_RDONLY);
//     if (fileFD < 0) {
//         perror("");
//         return;
//     }
//     char fileData[1024] {0};
//     int len = 0;
//     while (true) {
//         len = read(fileFD, fileData, sizeof(fileData));
//         if (len < 0) {
//             perror("");
//             break;
//         } else if (len == 0) {
//             break;
//         } else {
//             bufferevent_write(_buffEv, fileData, len);
//         }
//     }
//     std::cout << "发送文件完成" << std::endl;
//     close(fileFD);
// }

} // !namespace