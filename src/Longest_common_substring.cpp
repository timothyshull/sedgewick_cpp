#include <string>

#include "Longest_common_substring.h"
#include "Suffix_array.h"

std::string Longest_common_substring::lcp(std::string& s, int p, std::string& t, int q)
{
    auto n = std::min(s.size() - p, t.size() - q);
    for (auto i = 0; i < n; ++i) {
        if (s[p + i] != t[q + i]) {
            return s.substr(static_cast<std::string::size_type>(p), static_cast<std::string::size_type>(i));
        }
    }
    return s.substr(static_cast<std::string::size_type>(p), n);
}

int Longest_common_substring::compare(std::string& s, int p, std::string& t, int q)
{
    auto n = std::min(s.length() - p, t.length() - q);
    for (auto i = 0; i < n; ++i) {
        if (s[p + i] != t[q + i]) {
            return s[p + i] - t[q + i];
        }
    }
    if (s.length() - p < t.length() - q) { return -1; }
    else if (s.length() - p > t.length() - q) { return +1; }
    else { return 0; }
}

std::string Longest_common_substring::lcs(std::string& s, std::string& t)
{
    Suffix_array suffix1{s};
    Suffix_array suffix2{t};

    std::string lcs{""};
    auto i = 0;
    auto j = 0;
    int p;
    int q;
    while (i < s.length() && j < t.length()) {
        p = suffix1.index(i);
        q = suffix2.index(j);
        std::string x{lcp(s, p, t, q)};
        if (x.length() > lcs.length()) { lcs = x; }
        if (compare(s, p, t, q) < 0) { ++i; }
        else { ++j; }
    }
    return lcs;
}
