#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

#include <vector>
#include <string>

class Boyer_moore {
public:
    Boyer_moore(std::string& pat);
    Boyer_moore(std::vector<char>& pattern, int R);
    int search(std::string& txt);
    int search(std::vector<char>& text);
private:
    const int R;
    std::vector<int> right;
    std::vector<char> pattern;
    std::string pat;
};

#endif // BOYER_MOORE_H
