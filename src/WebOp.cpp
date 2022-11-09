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
    std::ignore = bufferevent_write(_buffEv, sendBuff, strlen(sendBuff));
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
            std::ignore = bufferevent_write(_buffEv, fileData, len);
        }
    }
    std::ignore = close(fileFD);
}