// Program 10.4 - LSD radix sort
#ifndef LSD_RADIX_SORT_H
#define LSD_RADIX_SORT_H

#include <vector>
#include <cmath>

#include "radix_util.h"

template<typename Item_t>
void radix_lsd(std::vector<Item_t>& coll, int l, int r)
{
    static std::vector<Item_t> aux;
    aux.reserve(aux.max_size() / 2);

    int i;
    int j;
    for (auto d = bytes_per_word - 1; d >= 0; --d) {
        std::vector<int> count(static_cast<std::vector<int>::size_type>(radix + 1), 0);
        for (i = l; i <= r; ++i) { count[digit(coll[i], d) + 1]++; }
        for (j = 1; j < radix; ++j) { count[j] += count[j - 1]; }
        for (i = l; i <= r; ++i) { aux[count[digit(coll[i], ++d)]] = coll[i]; }
        for (i = l; i <= r; ++i) { coll[i] = aux[i - l]; }
    }
}

template<typename Item_t>
void radix_sort(std::vector<Item_t>& coll, int n, int max)
{
    for (auto x = 0; x < max; ++x) {
        std::vector<std::vector<Item_t>> bins(
                static_cast<typename std::vector<std::vector<Item_t>>::size_type>(n),
                std::vector<Item_t>{}
        );
        for (auto y : coll) { bins[(y / static_cast<int>(std::pow(10, x))) % n].emplace_back(y); } // narrow_cast
        coll.clear();
        for (auto v : bins) { coll.insert(coll.end(), v.begin(), v.end()); }
    }
}

#endif // LSD_RADIX_SORT_H
