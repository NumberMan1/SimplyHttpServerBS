#ifndef WEBOP_H
#define WEBOP_H

class bufferevent;

namespace Web {

/** 通过bufferevent发送http响应报文
    @param _code 为状态码
    @param _info 为状态信息
    @param _filetype 为文件类型
    @param _len 为HTTP消息实体的传输长度
 */
void sendMsg(bufferevent *_buffEv, const int &_code,
             const char *_info, const char *_filetype,
             const int &_len);
/** 通过bufferevent发送文件
    @param _fileName 为文件路径名
 */
void sendFile(bufferevent *_buffEv, const char* _fileName);

} // ! namespace Web

#endif // ! WEBOP_H