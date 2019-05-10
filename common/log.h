#ifndef URL_DOWNLOADER_LOG_H
#define URL_DOWNLOADER_LOG_H

#include <fstream>
#include <time.h>

#include "common/macros.h"

namespace url_downloader {
namespace log {

static const char* log_file = "assets/download.log";

enum LogType {
    INFO_LOG = 0,
    WARN_LOG = 1,
    ERROR_LOG = 2,
    FATAL_LOG = 3,
};

static const char* g_LogInfo[] = {
    "Info: ",
    "Warning: ",
    "Error: ",
    "FatalL "
};

class Log {
public:
    ~Log() {
        of_.close();
    }
    void write(LogType type, const char* log) {
        if (!init_) {
            init();
        }
        of_ << get_timestr()
            << " "
            << g_LogInfo[type]
            << "    "
            << log
            << std::endl;
    }
private:
    void init() {
        of_.open(log_file, std::ios::app);
        if (!of_.is_open()) {
            return;
        }
        init_ = true;
    }
    std::string get_timestr() {
        time_t r_time;
        time(&r_time);
        struct tm t;
        localtime_r(&r_time, &t);
        char time_str[128] = {0};
        snprintf(time_str, sizeof(time_str), "%04d-%02d-%02d_%02d:%02d:%02d",
                 t.tm_year + 1900,
                 t.tm_mon + 1,
                 t.tm_mday,
                 t.tm_hour,
                 t.tm_min,
                 t.tm_sec);
        return std::string(time_str);
    }
private:
    std::ofstream of_;
    bool init_ = false;

SINGLETON_DECLARE(Log);
};

}  // namespace log
}  // url_downloader

#define INFO_LOG(log_data)                         \
    url_downloader::log::Log::instance()->write(   \
        url_downloader::log::INFO_LOG, log_data);
#define WARN_LOG(log_data)                         \
    url_downloader::log::Log::instance()->write(   \
        url_downloader::log::WARN_LOG, log_data);
#define ERROR_LOG(log_data)                        \
    url_downloader::log::Log::instance()->write(   \
        url_downloader::log::ERROR_LOG, log_data);
#define FATAL_LOG(log_data) \
    url_downloader::log::Log::instance()->write(url_downloader::log::FATAL_LOG, log_data);

#endif // DAILY_DOWNLOADER_LOG_H
