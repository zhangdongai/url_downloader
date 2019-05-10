#ifndef URL_DOWNLOADER_PARSER_H
#define URL_DOWNLOADER_PARSER_H

#include <functional>
#include <unordered_map>
#include <string>
#include <utility>

#include "common/macros.h"
#include "common/utils.h"

namespace url_downloader {
namespace dataparser {

enum class ParserType {
    INVALID = -1,
    BING_DAILY = 0,
    SHANBAY_DAILY = 1,
    MAX_NUM,
};

class Parser {
public:
    virtual ~Parser() {};
    virtual void parse(const char* const content) = 0;
    virtual void write_out(const std::string&);
    virtual const char* get_url() const {return url_;}

    static ParserType g_ParserType_;
protected:
    const char* url_ = nullptr;
};

class BingParser : public Parser {
public:
    virtual void parse(const char* const content);
SINGLETON_DECLARE(BingParser);
};

class ShanBayParser : public Parser {
public:
    virtual void parse(const char* const content);

SINGLETON_DECLARE(ShanBayParser);
};

using ParserFunc = std::function<Parser* ()>;
static const std::unordered_map<ParserType, ParserFunc, utils::EnumHash> g_ParserPairs = {
    {ParserType::BING_DAILY, std::bind(&BingParser::instance)},
    {ParserType::SHANBAY_DAILY, std::bind(&ShanBayParser::instance)},
};

}  // namespace dataparser
}  // namespace url_downloader

#endif // URL_DOWNLOADER_PARSER_H
