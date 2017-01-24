#ifndef SUFFIX_ARRAY_H
#define SUFFIX_ARRAY_H

#include <string>
#include <vector>

class Suffix {
public:
    Suffix(std::string& text, int index);

    char operator[](int i);

    bool operator<(Suffix& rhs);

    std::string toString();

private:
    const std::string text;
    const int index;

    int length();

};

class Suffix_array {
public:
    Suffix_array(std::string& text);

    int length();

    int index(int i);

    int lcp(int i);

    std::string select(int i);

    int rank(std::string& query);

private:
    std::vector<Suffix> suffixes;

    int lcp(Suffix& s, Suffix& t);

    int compar(std::string& query, Suffix& suffix);
};

#endif // SUFFIX_ARRAY_H
