// Program 10.3 - Three-way-radix quicksort
#ifndef THREE_WAY_RADIX_QUICKSORT_H
#define THREE_WAY_RADIX_QUICKSORT_H

#include <vector>

#include "insertion_sort.h"
#include "radix_util.h"

static const int qsort_cutoff = 10;

// TODO: check this -> is it assuming C-style strings
template<typename Item_t>
void quicksort_x(std::vector<Item_t>& coll, int l, int r, int d)
{
    auto ch = [d](long a) { return digit(a, d); };

    if (r - l <= qsort_cutoff) {
        insertion(coll, l, r);
        return;
    }

    auto v = ch(coll[r]);
    auto i = l - 1;
    auto j = r;
    auto p = l - 1;
    auto q = r;
    while (i < j) {
        while (ch(coll[++i]) < v) {}

        while (v < ch(coll[--j])) { if (j == l) { break; }}

        if (i > j) { break; }

        std::swap(coll[i], coll[j]);
        if (ch(coll[i]) == v) {
            ++p;
            std::swap(coll[p], coll[i]);
        }

        if (v == ch(coll[j])) {
            --q;
            std::swap(coll[j], coll[q]);
        }
    }

    if (p == q) {
        if (v != '\0') { quicksort_x(coll, l, r, d + 1); }
        return;
    }

    if (ch(coll[i]) < v) { ++i; }

    int k;
    for (k = l; k <= p; ++k, --j) { std::swap(coll[k], coll[j]); }
    for (k = r; k >= q; --k, ++i) { std::swap(coll[k], coll[i]); }

    quicksort_x(coll, l, j, d);

    if ((i == r) && (ch(coll[i]) == v)) { ++i; }
    if (v != '\0') { quicksort_x(coll, j + 1, i - 1, d + 1); }

    quicksort_x(coll, i, r, d);
}

#endif // THREE_WAY_RADIX_QUICKSORT_H
