// Program 10.2 - MSD radix sort
#ifndef MSD_RADIX_SORT_H
#define MSD_RADIX_SORT_H

#include "radix_util.h"
#include "insertion_sort.h"

static const int rsort_cutoff = 10;

template<typename Item_type>
void radix_msd(std::vector<Item_type> coll, int l, int r, int d)
{
    static std::vector<Item_type> aux;
    aux.reserve(aux.max_size() / 2);

    std::vector<int> count;
    count.reserve(static_cast<std::vector<int>::size_type>(radix + 1));

    auto bin = [l, &aux](int a) { return l + aux[a]; };

    if (d > bytes_per_word) { return; }

    if (r - l <= rsort_cutoff) {
        insertion(coll, l, r);
        return;
    }

    int j;
    for (j = 0; j < radix; ++j) { aux[j] = 0; }

    int i;
    for (i = l; i <= r; ++i) { aux[digit(coll[i], d) + 1]++; }

    for (j = 1; j < radix; ++j) { aux[j] += aux[j - 1]; }

    for (i = l; i <= r; ++i) { aux[aux[digit(coll[i], ++d)]] = coll[i]; }

    for (i = l; i <= r; ++i) { coll[i] = aux[i - l]; }

    radix_msd(coll, l, bin(0) - 1, d + 1);
    for (j = 0; j < radix - 1; ++j) { radix_msd(coll, bin(j), bin(j + 1) - 1, d + 1); }
}

#endif // MSD_RADIX_SORT_H
