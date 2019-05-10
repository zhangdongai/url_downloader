#include <iostream>

#include "downloader/downloader.h"
#include "common/log.h"
#include "dataparser/parser.h"

using url_downloader::dataparser::Parser;
using url_downloader::dataparser::ParserType;
using url_downloader::downloader::Downloader;

ParserType Parser::g_ParserType_ = ParserType::BING_DAILY;

int main(int argc, char** argv) {
    // parameters count shou be 2
    if (argc != 2) {
        ERROR_LOG("parameters count is wrong!");
        return 1;
    }
    Parser::g_ParserType_ = static_cast<ParserType>(std::stoi(argv[1]));
    if (Parser::g_ParserType_ <= ParserType::INVALID ||
        Parser::g_ParserType_ >= ParserType::MAX_NUM) {
        ERROR_LOG("parser type is out of range!");
        return 1;
    }
    std::cout << "begin to perform download" << std::endl;
    Downloader er;
    bool perform_ret = er.perform_download();
    return perform_ret ? 0 : 1;
}
