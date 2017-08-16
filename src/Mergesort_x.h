#ifndef MERGESORT_X_H
#define MERGESORT_X_H

#include <vector>
#include <gsl/gsl_util>

#include "Insertion_sort.h"
#include "sort_utility.h"
#include "utility.h"

// TODO: need to resolve sort ambiguity
namespace Mergesort_x {
    using namespace Sort_utility;

    static const int cutoff = 7;

    template<typename Item_t>
    static void merge(std::vector<Item_t> &src, std::vector<Item_t> &dst, int lo, int mid, int hi)
    {
        utility::alg_assert(
                std::is_sorted(src.begin() + lo, src.begin() + mid),
                "Mergesort_x is_sorted _check failed for lo to mid"
        );
        utility::alg_assert(
                std::is_sorted(src.begin() + mid + 1, src.begin() + hi),
                "Mergesort_x is_sorted _check failed for mid + 1 to hi"
        );

        auto i = lo;
        auto j = mid + 1;
        for (auto k = lo; k <= hi; ++k) {
            if (mid < i) {
                dst[k] = src[j++];
            } else if (hi < j) {
                dst[k] = src[i++];
            } else if (src[j] < src[i]) {
                dst[k] = src[j++];
            } else {
                dst[k] = src[i++];
            }
        }

        utility::alg_assert(std::is_sorted(dst.begin() + lo, dst.end() + hi), "Mergesort_x is_sorted _check failed");
    }

    template<typename Item_t>
    static void sort(std::vector<Item_t> &src, std::vector<Item_t> &dst, int lo, int hi)
    {
        if (hi <= lo + cutoff) {
            Insertion_sort::sort(dst, lo, hi);
            return;
        }
        int mid = lo + (hi - lo) / 2;
        sort(dst, src, lo, mid);
        sort(dst, src, mid + 1, hi);

        // if (src[mid] < src[mid + 1]) {
        //     for (auto i = lo; i <= hi; ++i) {
        //         dst[i] = src[i];
        //     }
        //     return;
        // }

        if (src[mid] < src[mid + 1]) {
            std::copy(src.begin() + lo, src.begin() + hi, dst.begin() + lo);
            return;
        }

        merge(src, dst, lo, mid, hi);
    }

    template<typename Item_t>
    static void sort(std::vector<Item_t> &coll)
    {
        auto aux = coll;
        sort(aux, coll, 0, coll.size() - 1);
        utility::alg_assert(std::is_sorted(coll.begin(), coll.end()), "Mergesort_x is_sorted check failed");
    }

    template<typename T, typename Comparator_t = std::less<T>>
    static void sort(std::vector<T> &a)
    {
        auto aux = a;
        sort(aux, a, 0, a.size() - 1);
        utility::alg_assert(
                std::is_sorted<decltype(a.begin()), Comparator_t>(a.begin(), a.end(), {}),
                "Mergesort_x is_sorted check failed"
        );
    }

    template<typename T, typename Comparator_t = std::less<T>>
    static void merge(std::vector<T> &src, std::vector<T> &dst, int lo, int mid, int hi)
    {
        auto comp = Comparator_t{};
        utility::alg_assert(
                std::is_sorted<decltype(src.begin()), Comparator_t>(src.begin() + lo, src.begin() + mid, comp),
                "Mergesort_x is_sorted _check failed for lo to mid"
        );
        utility::alg_assert(
                std::is_sorted<decltype(src.begin()), Comparator_t>(src.begin() + mid + 1, src.begin() + hi, comp),
                "Mergesort_x is_sorted _check failed for mid + 1 to hi"
        );

        auto i = lo;
        auto j = mid + 1;
        for (auto k = lo; k <= hi; ++k) {
            if (comp(mid, i)) {
                dst[k] = src[j++];
            } else if (comp(hi, j)) {
                dst[k] = src[i++];
            } else if (comp(src[j], src[i])) {
                dst[k] = src[j++];
            } else {
                dst[k] = src[i++];
            }
        }

        utility::alg_assert(
                std::is_sorted<decltype(dst.begin()), Comparator_t>(dst.begin() + lo, dst.begin() + hi, comp),
                "Mergesort_x is_sorted _check failed"
        );
    }

    template<typename Item_t, typename Comparator_t = std::less<Item_t>>
    static void sort(std::vector<Item_t> &src, std::vector<Item_t> &dst, int lo, int hi)
    {
        auto comp = Comparator_t{};
        if (hi <= lo + cutoff) {
            Insertion_sort::sort<Item_t, Comparator_t>(dst, lo, hi);
            return;
        }
        auto mid = (hi + lo) / 2;
        sort<Item_t, Comparator_t>(dst, src, lo, mid);
        sort<Item_t, Comparator_t>(dst, src, mid + 1, hi);

        if (!comp(src[mid + 1], src[mid])) {
            std::copy(src.begin() + lo, src.begin() + hi, dst.begin() + lo);
            return;
        }

        merge<Item_t, Comparator_t>(src, dst, lo, mid, hi);
    }
};

#endif // MERGESORT_X_H
