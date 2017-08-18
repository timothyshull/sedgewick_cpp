#ifndef QUICKSORT_3_WAY_H
#define QUICKSORT_3_WAY_H

#include <vector>
#include <gsl/gsl_util>

#include "Std_random.h"
#include "sort_utility.h"
#include "utility.h"

namespace Quicksort_3_way {
    using namespace Sort_utility;

    template<typename Item_t>
    void sort(std::vector<Item_t> &coll)
    {
        Std_random::shuffle(coll);
        sort(coll, 0, gsl::narrow_cast<int>(coll.size()) - 1);
        utility::alg_assert(std::is_sorted(coll.begin(), coll.end()), "Quicksort_3_way is_sorted check failed");
    }

    template<typename Item_t>
    void sort(std::vector<Item_t> &coll, int lo, int hi)
    {
        if (hi <= lo) { return; }
        auto lt = lo;
        auto gt = hi;
        auto v = coll[lo];
        auto i = lo;
        while (i <= gt) {
            if (coll[i] < v) {
                std::swap(coll[lt++], coll[i++]);
            } else if (v < coll[i]) {
                std::swap(coll[i], coll[gt--]);
            } else {
                ++i;
            }
        }

        sort(coll, lo, lt - 1);
        sort(coll, gt + 1, hi);
#ifndef NDEBUG
        utility::alg_assert(std::is_sorted(coll.begin() + lo, coll.begin() + hi), "Quicksort_3_way is_sorted check failed");
#endif
    }
};

#endif // QUICKSORT_3_WAY_H
