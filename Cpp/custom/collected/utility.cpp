#include <vector>
#include "utility.h"

void utility::alg_assert(bool test, const char* msg)
{
    if (!test) {
        std::fprintf(stderr, "%s\n", msg);
        std::abort();
    }
}

std::vector<char> utility::str_to_char_vector(std::string& str)
{
    std::vector<char> cv;
    for (int i{0}; i < str.size(); ++i) {
        cv.push_back(str[i]);
    }
    return cv;
}
