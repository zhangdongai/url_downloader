#include "downloader.h"

#include <iostream>
#include <cstring>

#include "dataparser/parser.h"
#include "common/log.h"

namespace url_downloader {
namespace downloader {

using dataparser::Parser;

void Downloader::init_curl() {
    curl_ = curl_easy_init();
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, Downloader::receive_data);
//    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, this);
}

bool Downloader::perform_download() {
    return perform_download(dataparser::g_ParserPairs.at(Parser::g_ParserType_)()->get_url());
}
bool Downloader::perform_download(const char* url) {
    curl_easy_setopt(curl_, CURLOPT_URL, url);
    CURLcode ret = curl_easy_perform(curl_);
    if (ret == CURLE_OK) {
        INFO_LOG("curl performed successfully!");
    }
    else {
        char error_info[128] = {0};
        snprintf(error_info, sizeof(error_info), "%s%d", "error code = ", static_cast<int32_t>(ret));
        ERROR_LOG(error_info);
        return false;
    }
    return true;
}

size_t Downloader::receive_data(const void* const data, size_t data_size,
                                size_t nmemb, void* user_data) {
    const char* const content = static_cast<const char* const>(data);
    size_t receive_size = strlen(content);
    
    char log_info[128] = {0};
    snprintf(log_info, sizeof(log_info), "%s%lu", "received data, data size = ", receive_size);
    INFO_LOG(log_info);

    dataparser::g_ParserPairs.at(Parser::g_ParserType_)()->parse(content);
    return receive_size;
}

}  // namespace downloader
}  // namespace url_downloader
