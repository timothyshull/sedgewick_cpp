#include <vector>
#include "utility.h"



std::vector<char> utility::str_to_char_vector(std::string const& str)
{
    auto cv = std::vector<char>(str.size());
    for (const auto c : str) {
        cv.emplace_back(c);
    }
    return cv;
}
