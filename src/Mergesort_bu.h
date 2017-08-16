#ifndef MERGESORT_BU_H
#define MERGESORT_BU_H

#include <vector>
#include <gsl/gsl_util>

#include "sort_utility.h"
#include "utility.h"

namespace Mergesort_bu {
    using namespace Sort_utility;

    template<typename Item_t>
    static void merge(std::vector<Item_t> &coll, std::vector<Item_t> &aux, int lo, int mid, int hi)
    {
        for (auto k = lo; k <= hi; ++k) {
            aux[k] = coll[k];
        }

        auto i = lo;
        auto j = mid + 1;
        for (auto k = lo; k <= hi; ++k) {
            if (mid < i) {
                coll[k] = aux[j++];
            } else if (hi < j) {
                coll[k] = aux[i++];
            } else if (aux[j] < aux[i]) {
                coll[k] = aux[j++];
            } else {
                coll[k] = aux[i++];
            }
        }
    }

    template<typename Item_t>
    static void sort(std::vector<Item_t> &coll)
    {
        auto n = gsl::narrow_cast<int>(coll.size());
        auto aux = std::vector<Item_t>(static_cast<typename std::vector<Item_t>::size_type>(n));
        for (auto len = 1; len < n; len *= 2) {
            for (auto lo = 0; lo < n - len; lo += len + len) {
                auto mid = lo + len - 1;
                auto hi = std::min(lo + len + len - 1, n - 1);
                merge(coll, aux, lo, mid, hi);
            }
        }
        utility::alg_assert(std::is_sorted(coll.begin(), coll.end()), "Mergesort_bu is_sorted check failed");
    }
};

#endif // MERGESORT_BU_H
