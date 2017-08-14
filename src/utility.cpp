#include <vector>
#include "utility.h"

void utility::alg_assert(bool test, char const* msg)
{
    if (!test) {
        fmt::fprintf(stderr, "%s\n", msg);
        std::abort();
    }
}

std::vector<char> utility::str_to_char_vector(std::string const& str)
{
    auto cv = std::vector<char>(str.size());
    for (const auto c : str) {
        cv.emplace_back(c);
    }
    return cv;
}
