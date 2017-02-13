#include <deque>
#include <sstream>
#include <gsl/gsl_util>

#include "Alphabet.h"
#include "utility.h"

Alphabet::Alphabet(std::string alpha)
        : _alphabet{alpha.begin(), alpha.end()},
          _radix(gsl::narrow<int, std::string::size_type>(alpha.length())),
          _inverse(static_cast<std::vector<int>::size_type>(std::numeric_limits<char>::max()), -1)
{
    std::deque<bool> unicode(static_cast<std::deque<bool>::size_type>(std::numeric_limits<char>::max()));
    char c;
    for (int i{0}; i < alpha.length(); ++i) {
        c = alpha[i];
        if (unicode[c]) {
            std::stringstream ss;
            ss << "Illegal alphabet: repeated character = '" << c << "'";
            throw utility::Illegal_argument_exception{ss.str()};
        }
        unicode[c] = true;
    }

    for (int i{0}; i < _radix; ++i) {
        _inverse[_alphabet[i]] = i;
    }
}

Alphabet::Alphabet(int radix)
        : _radix{radix},
          _alphabet(static_cast<std::vector<char>::size_type>(radix)),
          _inverse(static_cast<std::vector<int>::size_type>(radix))
{
    for (char i{0}; i < radix; ++i) {
        _inverse[i] = i; // ints
        _alphabet[i] = i;
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
    std::vector<int> target;
    target.reserve(s.length());
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
