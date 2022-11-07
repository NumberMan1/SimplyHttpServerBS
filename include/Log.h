#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string_view>

#define LOG(_message) Log::log((_message), __FILE__, __func__, __LINE__)

namespace Log {

// 可以直接使用宏LOG(消息)来给日志文件输入信息
void log(const std::string_view &_message,
         const std::string_view &_filename,
         const std::string_view &_func,
         const int &_line);

}

#endif // ! Log_H