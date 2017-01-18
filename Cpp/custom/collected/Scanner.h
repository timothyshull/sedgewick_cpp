#ifndef SCANNER_H
#define SCANNER_H

#include <regex>
#include <istream>
#include <boost/variant.hpp>

#include "LRU_cache.h"

using boost::variant;

class Scanner_lru_cache : public LRU_cache<std::string, std::regex> {
    std::regex create(std::string& s) { return std::regex(s); }

    bool has_name(std::regex& p, std::string& s) { return p == s; }
};

class Scanner {
private:
    const static int buffer_size{1024};

    char buf[buffer_size];
    int position;

    std::regex delim_pattern;
    std::regex has_next_pattern;
    int has_next_position;
    std::string has_next_result;
    std::istream source;
    bool source_closed = false;
    bool need_input = false;
    bool skipped = false;
    int saved_scanner_position = -1;

    variant<
            char, short, int, long, std::string,
            float, double, long long, long double
    > type_cache; // use type_cache.type() == typeid(type) (which() returns the type index)

    Scanner_lru_cache pattern_cache;

    std::ios_base::failure last_exception;

    static std::regex whitespace_pattern;
    static std::regex find_any_pattern;
    static std::regex non_ascii_digit;

    std::string group_separator{"\\."};
};

#endif // SCANNER_H
