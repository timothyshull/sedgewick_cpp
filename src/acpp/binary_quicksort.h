// Program 10.1 - Binary quicksort
#ifndef BINARY_QUICKSORT_H
#define BINARY_QUICKSORT_H

#include <vector>

#include "radix_util.h"


template<typename Item_type>
void quicksort_b(std::vector<Item_type>& coll, int l, int r, int d)
{
    auto i = l;
    auto j = r;
    if (r <= l || d > bits_per_word) { return; }
    while (j != i) {
        while (digit(coll[i], d) == 0 && (i < j)) { ++i; }
        while (digit(coll[j], d) == 1 && (j > i)) { j--; }
        std::swap(coll[i], coll[j]);
    }
    if (digit(coll[r], d) == 0) { ++j; }
    quicksort_b(coll, l, j - 1, d + 1);
    quicksort_b(coll, j, r, d + 1);
}

template<typename Item_type>
void sort(std::vector<Item_type>& coll, int l, int r) { quicksort_b(coll, l, r, 0); }

#endif // BINARY_QUICKSORT_H
