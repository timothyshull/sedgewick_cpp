#ifndef QUICKSORT_3_STRING_H
#define QUICKSORT_3_STRING_H

#include <string>
#include <vector>

#include "sort_utility.h"

namespace Quicksort_3_string {
    using namespace Sort_utility;

    static const int cutoff = 15;

    void sort(std::vector<std::string>& coll);

    int char_at(std::string const& s, int d);

    void sort(std::vector<std::string>& a, int lo, int hi, int d);
};

#endif // QUICKSORT_3_STRING_H
