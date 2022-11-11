#ifndef WEBOP_H
#define WEBOP_H

class bufferevent;

namespace Web {

/** 处理buffevent的事件回调
 *  BEV_EVENT_READING	0x01	< 读取时遇到错误
 *  BEV_EVENT_WRITING	0x02	< 写入时遇到错误
 *  BEV_EVENT_EOF		0x10	< Eof文件已达
 *  BEV_EVENT_ERROR		0x20	< 遇到无法恢复的错误
 *  BEV_EVENT_TIMEOUT	0x40	< 用户指定超时已达
 *  BEV_EVENT_CONNECTED	0x80	< 连接操作完成
    @param _buffEv 为相应的bufferevent指针
    @param _what 为事件
 */
void evHandle(bufferevent *_buffEv, short _what, void *_ctx);

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