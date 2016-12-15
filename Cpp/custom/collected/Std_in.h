#ifndef COLLECTED_STD_IN_H
#define COLLECTED_STD_IN_H

#include <string>
#include <locale>
#include <regex>

#include "Scanner.h"

class Std_in {
public:
    const static std::string charset_name;
    const static std::locale locale;
    const static std::regex whitespace_pattern;
    const static std::regex empty_pattern;
    const static std::regex everything_pattern;

    static Scanner scanner;

public:
    inline static is_empty() { return !scanner.has_next(); }
};

#endif //COLLECTED_STD_IN_H
