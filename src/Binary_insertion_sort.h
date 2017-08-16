#ifndef BINARY_INSERTION_H
#define BINARY_INSERTION_H

#include <vector>

#include "sort_utility.h"
#include "utility.h"


namespace Binary_insertion_sort {
    using namespace Sort_utility;

    template<typename Item_t>
    static void sort(std::vector<Item_t> &coll)
    {
        for (auto i = 1; i < coll.size(); ++i) {
            auto v = coll[i];
            auto lo = 0;
            auto hi = i;
            while (lo < hi) {
                auto mid = (hi + lo) / 2;
                if (v < coll[mid]) {
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
            }

            for (auto j = i; j > lo; --j) {
                coll[j] = coll[j - 1];
            }
            coll[lo] = v;
        }
        utility::alg_assert(
                std::is_sorted(coll.begin(), coll.end()),
                "The Binary_insertion_sort is_sorted check failed"
        );
    }
};

#endif // BINARY_INSERTION_H
