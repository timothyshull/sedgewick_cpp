#include <deque>
#include <sstream>
#include "Alphabet.h"
#include "utility.h"

Alphabet::Alphabet(std::string alpha)
{
    std::deque<bool> unicode(static_cast<typename std::deque<bool>::size_type>(std::numeric_limits<char>::max()));
    for (int i{0}; i < alpha.length(); ++i) {
        char c = alpha[i];
        if (unicode[c]) {
            std::stringstream ss;
            ss << "Illegal alphabet: repeated character = '" << c << "'";
            throw utility::Illegal_argument_exception(ss.str());
        }
        unicode[c] = true;
    }

    _alphabet = std::vector<char>(alpha.length());
    for (int i{0}; i < alpha.length(); ++i) {
        _alphabet[i] = alpha[i];
    }
    _radix = alpha.length();
    _inverse = std::vector<int>(static_cast<std::vector<int>::size_type>(std::numeric_limits<char>::max()));
    for (int i{0}; i < _inverse.size(); ++i) {
        _inverse[i] = -1;
    }

    for (int c{0}; c < _radix; ++c) {
        _inverse[_alphabet[c]] = c;
    }
}

Alphabet::Alphabet(int radix)
        : _radix{radix},
          _alphabet(static_cast<std::vector<char>::size_type>(radix)),
          _inverse(static_cast<std::vector<int>::size_type(radix))
{
    for (int i{0}; i < radix; ++i) {
        _alphabet[i] = static_cast<char>(i);
    }
    for (int i{0}; i < radix; ++i) {
        _inverse[i] = i;
    }
}

int Alphabet::lg_r() const
{
    int lg_r{0};
    for (int t{_radix - 1}; t >= 1; t /= 2) {
        ++lg_r;
    }
    return lg_r;
}

std::vector<int> Alphabet::to_indices(std::string s) const
{
    std::vector<int> target(s.length());
    for (int i{0}; i < s.length(); ++i) {
        target[i] = to_index(s[i]);
    }
    return target;
}

std::string Alphabet::to_chars(std::vector<int> indices) const
{
    std::stringstream ss;
    for (auto i : indices) {
        ss << to_char(i);
    }
    return ss.str();
}
