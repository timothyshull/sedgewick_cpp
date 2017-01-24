#include <deque>
#include <sstream>
#include "Alphabet.h"
#include "utility.h"

Alphabet::Alphabet(std::string alpha)
{
    std::deque<bool> unicode(static_cast<typename std::deque<bool>::size_type>(CHAR_MAX));
    for (int i = 0; i < alpha.length(); ++i) {
        char c = alpha[i];
        if (unicode[c]) {
            std::stringstream ss;
            ss << "Illegal alphabet: repeated character = '" << c << "'";
            throw utility::Illegal_argument_exception(ss.str());
        }
        unicode[c] = true;
    }

    _alphabet = std::vector<char>(alpha.length());
    for (int i = 0; i < alpha.length(); ++i) {
        _alphabet[i] = alpha[i];
    }
    _radix = alpha.length();
    _inverse = std::vector<int>(CHAR_MAX);
    for (int i = 0; i < _inverse.size(); ++i) {
        _inverse[i] = -1;
    }

    for (int c = 0; c < _radix; ++c) {
        _inverse[_alphabet[c]] = c;
    }
}

Alphabet::Alphabet(int radix) : _radix{radix}
{
    _alphabet = std::vector<char>(radix);
    _inverse = std::vector<int>(radix);

    for (int i = 0; i < radix; ++i) {
        _alphabet[i] = static_cast<char>(i);
    }
    for (int i = 0; i < radix; ++i) {
        _inverse[i] = i;
    }
}

int Alphabet::lg_r() const
{
    int lgR = 0;
    for (int t = _radix - 1; t >= 1; t /= 2) {
        lgR++;
    }
    return lgR;
}

std::vector<int> Alphabet::to_indices(std::string s) const
{
    std::vector<int> target(s.length());
    for (int i = 0; i < s.length(); ++i) {
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
