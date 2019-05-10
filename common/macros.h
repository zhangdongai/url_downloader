#ifndef URL_DOWNLOADER_MACROS_H
#define URL_DOWNLOADER_MACROS_H

#define SINGLETON_DECLARE(CLASS) \
public:                          \
    static CLASS* instance() {   \
        static CLASS instance;   \
        return &instance;        \
    }                            \
private:                         \
    CLASS();                     \
    CLASS(const CLASS&);         \
    CLASS& operator = (const CLASS&);

#endif
