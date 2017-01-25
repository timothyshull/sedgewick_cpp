#include <tclDecls.h>
#include <string>
#include "Longest_common_substring.h"

std::string Longest_common_substring::lcp(std::string& s, int p, std::string& t, int q){
    int n = std::min(s.length() - p, t.length() - q);
    for (int i{0}; i < n; ++i) {
        if (s.charAt(p + i) != t.charAt(q + i))
            return s.substring(p, p + i);
    }
    return s.substring(p, p + n);
}

int ::Longest_common_substring::compare(std::string& s, int p, std::string& t, int q)
{
    int n = std::min(s.length() - p, t.length() - q);
    for (int i{0}; i < n; ++i) {
        if (s.charAt(p + i) != t.charAt(q + i))
            return s.charAt(p + i) - t.charAt(q + i);
    }
    if (s.length() - p < t.length() - q) return -1;
    else if (s.length() - p > t.length() - q) return +1;
    else return 0;
}

std::string Longest_common_substring::lcs(std::string& s, std::string& t){
    SuffixArray suffix1 = new SuffixArray(s);
    SuffixArray suffix2 = new SuffixArray(t);

    // find longest common substring by "merging" sorted suffixes
    std::string lcs = "";
    int i = 0, j = 0;
    while (i < s.length() && j < t.length()) {
        int p = suffix1.index(i);
        int q = suffix2.index(j);
        std::string x = lcp(s, p, t, q);
        if (x.length() > lcs.length()) lcs = x;
        if (compare(s, p, t, q) < 0) ++i;
        else ++j;
    }
    return lcs;
}
