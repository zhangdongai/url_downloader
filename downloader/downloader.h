#ifndef URL_DOWNLOADER_DOWNLOADER_H
#define URL_DOWNLOADER_DOWNLOADER_H

#include <curl/curl.h>

#include "dataparser/parser.h"

namespace url_downloader {
namespace downloader {
class Downloader {
public:
    Downloader() {
        init_curl();
    }
    ~Downloader() {
        if (curl_) {
            curl_easy_cleanup(curl_);
            curl_ = nullptr;
        }
    }
    void init_curl();
    bool perform_download();
    bool perform_download(const char* url);
    static size_t receive_data(const void* const data, size_t data_size, size_t nmemb, void* user_data);
private:
    CURL* curl_;
};
}  // namespace downloader
}  // namespace url_downloader

#endif // URL_DOWNLOADER_DOWNLOADER_H


