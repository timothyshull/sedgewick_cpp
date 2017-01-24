#ifndef SUFFIX_ARRAY_X_H
#define SUFFIX_ARRAY_X_H

#include <vector>

class Suffix_array_x {
public:
    Suffix_array_x(std::string& text);

    int length();

    int index(int i);

    int lcp(int i);

    std::string select(int i);

    int rank(std::string& query);

private:
    const static int CUTOFF = 5;
    const std::vector<char> text;
    const std::vector<int> index;
    const int n;

    void sort(int lo, int hi, int d);

    void insertion(int lo, int hi, int d);

    bool less(int i, int j, int d);

    void exch(int i, int j);

    int lcp(int i, int j);

    int compare(std::string& query, int i);
};

#endif // SUFFIX_ARRAY_X_H
