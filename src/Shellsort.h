#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <vector>
#include <gsl/gsl_util>

#include "sort_utility.h"
#include "utility.h"

namespace Shellsort {
    using namespace Sort_utility;

    template<typename Item_t>
    void sort(std::vector<Item_t> &coll)
    {
        auto n = gsl::narrow_cast<int>(coll.size());

        auto h = 1;
        while (h < n / 3) {
            h = 3 * h + 1;
        }

        while (h >= 1) {
            for (auto i = h; i < n; ++i) {
                for (auto j = i; h <= j && coll[j] < coll[j - h]; j -= h) {
                    std::swap(coll[j], coll[j - h]);
                }
            }
            utility::alg_assert(
                    std::is_sorted(coll.begin() + h, coll.end()),
                    "Shellsort is_h_sorted check failed"
            ); // is_h_sorted
            h /= 3;
        }
        utility::alg_assert(std::is_sorted(coll.begin(), coll.end()), "Shellsort is_sorted check failed");
    }
};

#endif // SHELLSORT_H
