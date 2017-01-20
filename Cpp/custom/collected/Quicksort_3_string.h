#ifndef QUICKSORT_3_STRING_H
#define QUICKSORT_3_STRING_H

#include <string>
#include <vector>
#include "Std_random.h"

namespace Quicksort_3_string {
    static const int cutoff = 15;

    void sort(std::vector<std::string>& a);

    int char_at(std::string& s, int d);

    void sort(std::vector<std::string>& a, int lo, int hi, int d);

    void insertion(std::vector<std::string>& a, int lo, int hi, int d);

    void exch(std::vector<std::string>& a, int i, int j);

    bool less(std::string& v, std::string w, int d);

    bool is_sorted(std::vector<std::string>& a);
};

#endif // QUICKSORT_3_STRING_H
