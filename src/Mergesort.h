#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>
#include <gsl/gsl_util>

#include "sort_utility.h"
#include "utility.h"

namespace Mergesort {
    using namespace Sort_utility;

    template<typename Item_t>
    void merge(
            std::vector<Item_t> &coll,
            std::vector<int> &index,
            std::vector<int> &aux,
            int lo,
            int mid,
            int hi
    )
    {
        for (auto k = lo; k <= hi; ++k) {
            aux[k] = index[k];
        }

        auto i = lo;
        auto j = mid + 1;
        for (auto k = lo; k <= hi; ++k) {
            if (i > mid) {
                index[k] = aux[j++];
            } else if (j > hi) {
                index[k] = aux[i++];
            } else if (coll[aux[j]] < coll[aux[i]]) {
                index[k] = aux[j++];
            } else {
                index[k] = aux[i++];
            }
        }
    }

    template<typename Item_t>
    void merge(std::vector<Item_t> &coll, std::vector<Item_t> &aux, int lo, int mid, int hi)
    {
        utility::alg_assert(
                std::is_sorted(coll.begin() + lo, coll.begin() + mid),
                "Mergesort is_sorted check failed for lo to mid"
        );
        utility::alg_assert(
                std::is_sorted(coll.begin() + mid + 1, coll.begin() + hi),
                "Mergesort is_sorted check failed for mid + 1 to hi"
        );

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

        utility::alg_assert(std::is_sorted(coll.begin() + lo, coll.begin() + hi), "Mergesort is_sorted check failed");
    }

    template<typename Item_t>
    void sort(std::vector<Item_t> &coll, std::vector<Item_t> &aux, int lo, int hi)
    {
        if (hi <= lo) {
            return;
        }
        auto mid = (hi + lo) / 2;
        sort<Item_t>(coll, aux, lo, mid);
        sort<Item_t>(coll, aux, mid + 1, hi);
        merge<Item_t>(coll, aux, lo, mid, hi);
    }

    template<typename Item_t>
    void sort(std::vector<Item_t> &coll)
    {
        auto n = gsl::narrow_cast<int>(coll.size());
        auto aux = std::vector<Item_t>(static_cast<typename std::vector<Item_t>::size_type>(n));
        sort<Item_t>(coll, aux, 0, n - 1);
        utility::alg_assert(std::is_sorted(coll.begin(), coll.end()), "Mergesort is_sorted check failed");
    }

    template<typename Item_t>
    void sort(std::vector<Item_t> &coll, std::vector<int> &index, std::vector<int> &aux, int lo, int hi)
    {
        if (hi <= lo) {
            return;
        }
        auto mid = (hi + lo) / 2;
        sort<Item_t>(coll, index, aux, lo, mid);
        sort<Item_t>(coll, index, aux, mid + 1, hi);
        merge<Item_t>(coll, index, aux, lo, mid, hi);
    }

    template<typename Item_t>
    std::vector<int> index_sort(std::vector<Item_t> &coll)
    {
        auto n = gsl::narrow_cast<int>(coll.size());
        auto index = std::vector<int>(static_cast<std::vector<int>::size_type>(n));
        for (auto i = 0; i < n; ++i) {
            index[i] = i;
        }

        auto aux = std::vector<int>(static_cast<std::vector<int>::size_type>(n));
        sort<Item_t>(coll, index, aux, 0, n - 1);
        return index;
    }
};

#endif // MERGE_SORT_H
