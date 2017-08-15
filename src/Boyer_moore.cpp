#include "Boyer_moore.h"

Boyer_moore::Boyer_moore(std::string& pattern_str)
        : _radix{256},
          _pattern_str{pattern_str},
          _right(static_cast<std::vector<int>::size_type>(_radix))
{
    for (auto c = 0; c < _radix; ++c) {
        _right[c] = -1;
    }
    for (auto j = 0; j < pattern_str.size(); ++j) {
        _right[pattern_str[j]] = j;
    }
}

Boyer_moore::Boyer_moore(std::vector<char>& pattern, int radix)
        : _radix{radix},
          _pattern{pattern},
          _right(static_cast<std::vector<int>::size_type>(_radix))
{
    for (auto c = 0; c < radix; ++c) {
        _right[c] = -1;
    }
    for (auto j = 0; j < pattern.size(); ++j) {
        _right[pattern[j]] = j;
    }
}

int Boyer_moore::search(std::string& txt)
{
    auto m = static_cast<int>(_pattern_str.size());
    auto n = static_cast<int>(txt.size());
    int skip;
    for (auto i = 0; i <= n - m; i += skip) {
        skip = 0;
        for (auto j = m - 1; j >= 0; j--) {
            if (_pattern_str[j] != txt[i + j]) {
                skip = std::max(1, j - _right[txt[i + j]]);
                break;
            }
        }
        if (skip == 0) { return i; }
    }
    return n;
}

int Boyer_moore::search(std::vector<char>& text)
{
    auto m = static_cast<int>(_pattern.size());
    auto n = static_cast<int>(text.size());
    int skip;
    for (auto i = 0; i <= n - m; i += skip) {
        skip = 0;
        for (auto j = m - 1; j >= 0; j--) {
            if (_pattern[j] != text[i + j]) {
                skip = std::max(1, j - _right[text[i + j]]);
                break;
            }
        }
        if (skip == 0) { return i; }
    }
    return n;
}
