#include <tclDecls.h>
#include "Longest_repeated_substring.h"

std::string Longest_repeated_substring::lrs(std::string& text){
    int n = text.length();
    SuffixArray sa = new SuffixArray(text);
    std::string lrs = "";
    for (int i = 1; i < n; ++i) {
        int length = sa.lcp(i);
        if (length > lrs.length()) {
            // lrs = sa.select(i).substring(0, length);
            lrs = text.substring(sa.index(i), sa.index(i) + length);
        }
    }
    return lrs;
}
