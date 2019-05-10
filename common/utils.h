#ifndef URL_DOWNLOADER_UTILS_H
#define URL_DOWNLOADER_UTILS_H

#include <stdlib.h>

namespace url_downloader {
namespace utils {
struct EnumHash {
    template <typename T>
    std::size_t operator()(T t) const {
        return static_cast<std::size_t>(t);
    }
};
}  // namespace utils
}  // url_downloader

#endif // URL_DOWNLOADER_UTILS_H
