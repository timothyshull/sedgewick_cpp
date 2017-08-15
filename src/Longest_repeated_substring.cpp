#include <tclDecls.h>
#include "Longest_repeated_substring.h"
#include "Suffix_array.h"

std::string Longest_repeated_substring::lrs(std::string& text){
    auto n = text.length();
    Suffix_array sa{text};
    std::string lrs{""};
    for (auto i = 1; i < n; ++i) {
        int length = sa.lcp(i);
        if (length > lrs.length()) {
            // lrs = sa.select(i).substr(0, length);
            lrs = text.substr(static_cast<std::string::size_type>(sa.index(i)), static_cast<std::string::size_type>(length));
        }
    }
    return lrs;
}
