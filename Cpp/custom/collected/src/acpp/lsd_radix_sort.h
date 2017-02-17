// Program 10.4 - LSD radix sort
#ifndef LSD_RADIX_SORT_H
#define LSD_RADIX_SORT_H

#include <vector>

#include "radix_util.h"

template<typename Item_type>
void radixLSD(std::vector<Item_type> a, int l, int r)
{
    static std::vector<Item_type> aux;
    aux.reserve(aux.max_size() / 2);

    for (int d{bytes_per_word - 1}; d >= 0; --d) {
        int i;
        int j;
        std::vector<int> count;
        count.assign(static_cast<std::vector<int>::size_type>(radix + 1), 0);

        // for (j = 0; j < radix; ++j) { count[j] = 0; }

        for (i = l; i <= r; ++i) { count[digit(a[i], d) + 1]++; }

        for (j = 1; j < radix; ++j) { count[j] += count[j - 1]; }

        for (i = l; i <= r; ++i) { aux[count[digit(a[i], ++d)]] = a[i]; }

        for (i = l; i <= r; ++i) { a[i] = aux[i - l]; }
    }
}

#endif // LSD_RADIX_SORT_H
