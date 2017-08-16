#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <vector>
#include <gsl/gsl_util>

#include "sort_utility.h"
#include "utility.h"

namespace Bubblesort {
    using namespace Sort_utility;

    template<typename Item_t>
    static void sort(std::vector<Item_t> &coll)
    {
        auto n = gsl::narrow_cast<int>(coll.size());
        for (auto i = 0; i < n; ++i) {
            auto exchanges = 0;
            for (auto j = n - 1; j > i; --j) {
                if (coll[j] < coll[j - 1]) {
                    std::swap(coll[j], coll[j - 1]);
                    ++exchanges;
                }
            }
            if (exchanges == 0) {
                break;
            }
        }
        utility::alg_assert(std::is_sorted(coll.begin(), coll.end()), "The Bubblesort is_sorted check failed");
    }
};

#endif // BUBBLE_SORT_H
