#include "parser.h"

#include <fstream>
#include "json.hpp"

#include "common/log.h"

namespace url_downloader {
namespace dataparser {

using Json = nlohmann::json;

void Parser::write_out(const std::string& content) {
    std::ofstream of("assets/download.url");
    if (!of.is_open()) {
        return;
    }
    of << content.data() << std::endl;
    of.close();
}

BingParser::BingParser() {
    url_ = "http://cn.bing.com/HPImageArchive.aspx?format=js&idx=0&n=1";
}

void BingParser::parse(const char* const content) {
    std::cout << "BingParser parser called" << std::endl;
    if (!content) {
        return;
    }

    Json json;
    try {
        json = Json::parse(content);
    }
    catch(const std::exception& e) {
        std::string error_info(e.what());
        error_info = "exception occurs: " + error_info;
        ERROR_LOG(error_info.data());
        return;
    }
    auto image_con = json["images"];
    std::string url = image_con[0]["url"];
    url = "http://s.cn.bing.net" + url;
    std::cout << url << std::endl;
    INFO_LOG(url.data());
    write_out(url);
}

ShanBayParser::ShanBayParser() {
    url_ = "http://cn.bing.com/HPImageArchive.aspx?format=js&idx=0&n=1";
}

void ShanBayParser::parse(const char* const content) {
    std::cout << "ShanBayParser parser called" << std::endl;
}

}  // namespace dataparser
}  // namespace url_downloader
