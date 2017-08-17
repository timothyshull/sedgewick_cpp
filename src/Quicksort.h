#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include <gsl/gsl_util>

#include "sort_utility.h"
#include "utility.h"
#include "Std_random.h"

namespace Quicksort {
    using namespace Sort_utility;

    template<typename Item_t>
    int partition(std::vector<Item_t> &coll, int lo, int hi)
    {
        auto i = lo;
        auto j = hi + 1;
        auto v = coll[lo];
        while (true) {
            while (coll[++i] < v) {
                if (i == hi) { break; }
            }

            while (v < coll[--j]) {
                if (j == lo) { break; }
            }

            if (i >= j) { break; }
            std::swap(coll[i], coll[j]);
        }

        std::swap(coll[lo], coll[j]);
        return j;
    }

    template<typename Item_t>
    void sort(std::vector<Item_t> &coll, int lo, int hi)
    {
        if (hi <= lo) { return; }
        int j = partition(coll, lo, hi);
        sort(coll, lo, j - 1);
        sort(coll, j + 1, hi);
        utility::alg_assert(std::is_sorted(coll.begin() + lo, coll.begin() + hi), "Quicksort is_sorted check failed");
    }

    template<typename Item_t>
    void sort(std::vector<Item_t> &coll)
    {
        Std_random::shuffle(coll);
        sort(coll, 0, gsl::narrow_cast<int>(coll.size()) - 1);
        utility::alg_assert(std::is_sorted(coll.begin(), coll.end()), "Quicksort is_sorted check failed");
    }

    template<typename Item_t>
    Item_t select(std::vector<Item_t> &coll, int k)
    {
        if (k < 0 || k >= coll.size()) {
            throw utility::Index_out_of_bounds_exception{"Selected element out of bounds"};
        }
        // Std_random::shuffle(coll);

        auto lo = 0;
        auto hi = gsl::narrow_cast<int>(coll.size()) - 1;
        while (hi > lo) {
            auto i = partition(coll, lo, hi);
            if (k < i) {
                hi = i - 1;
            } else if (i < k) {
                lo = i + 1;
            } else {
                return coll[i];
            }
        }
        return coll[lo];
    }
};

#endif // QUICKSORT_H
