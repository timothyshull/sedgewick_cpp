#ifndef LONGEST_COMMON_SUBSTRING_H
#define LONGEST_COMMON_SUBSTRING_H

#include <string>

namespace Longest_common_substring {
    std::string lcp(std::string& s, int p, std::string& t, int q);

    int compare(std::string& s, int p, std::string& t, int q);

    std::string lcs(std::string& s, std::string& t);
};

#endif // LONGEST_COMMON_SUBSTRING_H
