#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <algorithm>
#include <gsl/gsl_util>

#include "sort_utility.h"
#include "utility.h"

namespace Selection_sort {
    using namespace Sort_utility;

    template<typename Item_t, typename Comparator_t = std::less<Item_t>>
    void sort(std::vector<Item_t>& coll)
    {
        auto comp = Comparator_t{};
        auto n = gsl::narrow_cast<int>(coll.size());
        for (auto i = 0; i < n; ++i) {
            auto min = i;
            for (auto j = i + 1; j < n; ++j) {
                if (comp(coll[j], coll[min])) {
                    min = j;
                }
            }
            std::swap(coll[i], coll[min]);
#ifndef NDEBUG
            utility::alg_assert(
                    std::is_sorted<decltype(coll.begin()), Comparator_t>(coll.begin(), coll.begin() + i, comp),
                    "Selection_sort is_sorted range check failed"
            );
#endif
        }
#ifndef NDEBUG
        utility::alg_assert(
                std::is_sorted<decltype(coll.begin()), Comparator_t>(coll.begin(), coll.end(), comp),
                "Selection_sort is_sorted check failed"
        );
#endif
    }
};

#endif // SELECTION_SORT_H
