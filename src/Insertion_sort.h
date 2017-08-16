#ifndef INSERTION_H
#define INSERTION_H

#include <vector>
#include <gsl/gsl_util>

#include "sort_utility.h"
#include "utility.h"

namespace Insertion_sort {
    using namespace Sort_utility;

    template<typename Item_t, typename Comparator_t = std::less<Item_t>>
    static void sort(std::vector<Item_t> &coll)
    {
        auto comp = Comparator_t{};
        auto n = gsl::narrow_cast<int>(coll.size());
        for (auto i = 0; i < n; ++i) {
            for (auto j = i; 0 < j && comp(coll[j], coll[j - 1]); --j) {
                std::swap(coll[j], coll[j - 1]);
            }
        }
        utility::alg_assert(std::is_sorted(coll.begin(), coll.end()), "The Insertion_sort is_sorted check failed");
    }

    template<typename T, typename Comparator_t>
    static void sort(std::vector<T> &coll, int lo, int hi)
    {
        auto comp = Comparator_t{};
        for (auto i = lo; i <= hi; ++i) {
            for (auto j = i; lo < j && comp(coll[j], coll[j - 1]); --j) {
                std::swap(coll[j], coll[j - 1]);
            }
        }
        utility::alg_assert(std::is_sorted(coll.begin(), coll.end()), "The Insertion_sort is_sorted check failed");
    }

    template<typename T>
    static std::vector<int> index_sort(std::vector<T> &coll)
    {
        auto n = gsl::narrow_cast<int>(coll.size());
        auto index = std::vector<int>(coll.size());
        for (auto i = 0; i < n; ++i) {
            index[i] = i;
        }

        for (auto i = 0; i < n; ++i) {
            for (auto j = i; 0 < j && coll[index[j]] < coll[index[j - 1]]; --j) {
                std::swap(index[j], index[j - 1]);
            }
        }

        return index;
    }
};

#endif // INSERTION_H
