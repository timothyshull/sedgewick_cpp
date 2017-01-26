#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

#include <vector>
#include <string>

class Boyer_moore {
public:
    Boyer_moore() = default;

    Boyer_moore(const Boyer_moore&) = default;

    Boyer_moore(Boyer_moore&&) = default;

    ~Boyer_moore() = default;

    Boyer_moore& operator=(const Boyer_moore&) = default;

    Boyer_moore& operator=(Boyer_moore&&) = default;

    Boyer_moore(std::string& pattern_str);

    Boyer_moore(std::vector<char>& pattern, int R);

    int search(std::string& txt);

    int search(std::vector<char>& text);

private:
    const int _radix;
    std::vector<int> _right;
    std::vector<char> _pattern;
    std::string _pattern_str;
};

#endif // BOYER_MOORE_H
