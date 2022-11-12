#include "Log.h"

char* Log::Time::Now() noexcept {
    using namespace std::chrono;
    auto &&time = system_clock::now();
    time_t &&tt = system_clock::to_time_t(time);  //数据截断
    auto &&time_tm = localtime(&tt);              // C格式函数
    sprintf(strTime, "%d-%02d-%02d %02d:%02d:%02d", time_tm->tm_year + 1900,
            time_tm->tm_mon + 1, time_tm->tm_mday, time_tm->tm_hour,
            time_tm->tm_min, time_tm->tm_sec);
    return strTime;
}
char Log::Time::strTime[40] {};

void Log::log(const std::string_view &_message,
         const std::string_view &_filename,
         const std::string_view &_func,
         const int &_line) {
    using OpenMode = std::ios_base::openmode;
    std::ofstream log("./log/d.log", OpenMode::_S_app);
    log << "info: " << _filename << ':' << _line << '\n'
        << "时间为: " << Time::Now() << '\n'
        << _func << ": " << _message << '\n';
}

