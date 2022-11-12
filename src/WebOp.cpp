#include "WebOp.h"

#include <cstring>

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "MLibEvent.h"

void 
Web::sendMsg(bufferevent *_buffEv, const int &_code,
             const char *_info, const char *_filetype,
             const int &_len)
{
    char sendBuff[1024] {0};
    std::ignore = sprintf(sendBuff, "HTTP/1.1 %d %s\r\n", _code, _info);
    std::ignore = sprintf(sendBuff + strlen(sendBuff),
                          "Content-Type:%s\r\n", _filetype);
    if (_len > 0) {
        std::ignore = sprintf(sendBuff + strlen(sendBuff),
                              "Content-Length:%d\r\n", _len);
    }
    std::ignore = strcat(sendBuff, "\r\n");
    if(bufferevent_write(_buffEv, sendBuff, strlen(sendBuff)) == -1) {
        bufferevent_free(_buffEv);
    }
}

void
Web::sendFile(bufferevent *_buffEv, const char *_fileName) {
    int fileFD = open(_fileName, O_RDONLY);
    if (fileFD < 0) {
        perror("");
        return;
    }
    char fileData[1024] {0};
    int len = 0;
    while (true) {
        len = read(fileFD, fileData, sizeof(fileData));
        if (len < 0) {
            perror("");
            break;
        } else if (len == 0) {
            break;
        } else {
            if (bufferevent_write(_buffEv, fileData, len) == -1 ) {
                bufferevent_free(_buffEv);
                LOG("发送失败");
                close(fileFD);
                return;
            }
        }
    }
    std::ignore = close(fileFD);
}

void
Web::evHandle(bufferevent *_buffEv, short _what, void *_arg) {
    if (_what & BEV_EVENT_EOF) // 连接关闭
        LOG("连接关闭");
    else if (_what & BEV_EVENT_ERROR) // 连接错误
        LOG("some other error\n");
    else if (_what & BEV_EVENT_WRITING) 
        LOG("写入出错");
    else if(_what & BEV_EVENT_CONNECTED) { // 连接成功，回调直接退出
        LOG("用户连接成功\n");
        return;
    }
    // 运行到这里已经可以确定连接关闭或者错误，则清楚内存。
    bufferevent_free(_buffEv);
}