#ifndef INSERTION_X_H
#define INSERTION_X_H

#include <vector>
#include <gsl/gsl_util>

#include "sort_utility.h"
#include "utility.h"

namespace Insertion_sort_x {
    using namespace Sort_utility;

    template<typename Item_t>
    static void sort(std::vector<Item_t> &coll)
    {
        auto n = gsl::narrow_cast<int>(coll.size());

        auto exchanges = 0;
        for (auto i = n - 1; i > 0; i--) {
            if (coll[i] < coll[i - 1]) {
                std::swap(coll[i], coll[i - 1]);
                ++exchanges;
            }
        }
        if (exchanges == 0) {
            return;
        }

        for (auto i = 2; i < n; ++i) {
            auto v = coll[i];
            auto j = i;
            while (v < coll[j - 1]) {
                coll[j] = coll[j - 1];
                --j;
            }
            coll[j] = v;
        }

        utility::alg_assert(std::is_sorted(coll.begin(), coll.end()), "Insertion_sort_x is_sorted check failed");
    }
};

#endif // INSERTION_X_H
