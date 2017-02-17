#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "utility.h"
#include "Std_random.h"
#include "Std_out.h"

class Quicksort {
public:
    template<typename T>
    static void sort(std::vector<T>& a)
    {
        Std_random::shuffle(a);
        sort(a, 0, static_cast<int>(a.size() - 1)); // narrow_cast
        utility::alg_assert(is_sorted(a), "Quicksort is_sorted _check failed");
    }

    template<typename T>
    static void sort(std::vector<T>& a, int lo, int hi)
    {
        if (hi <= lo) { return; }
        int j = partition(a, lo, hi);
        sort(a, lo, j - 1);
        sort(a, j + 1, hi);
        utility::alg_assert(is_sorted(a, lo, hi), "Quicksort is_sorted _check failed");
    }

    template<typename T>
    static int partition(std::vector<T>& a, int lo, int hi)
    {
        int i = lo;
        int j = hi + 1;
        T v = a[lo];
        while (true) {
            while (less(a[++i], v)) {
                if (i == hi) { break; }
            }

            while (less(v, a[--j])) {
                if (j == lo) { break; }
            }

            if (i >= j) { break; }
            exch(a, i, j);
        }

        exch(a, lo, j);
        return j;
    }

    template<typename T>
    static T select(std::vector<T>& a, int k)
    {
        if (k < 0 || k >= a.size()) {
            throw utility::Index_out_of_bounds_exception("Selected element out of bounds");
        }
        Std_random::shuffle(a);
        int lo{0};
        int hi{static_cast<int>(a.size() - 1)}; // narrow_cast
        while (hi > lo) {
            int i = partition(a, lo, hi);
            if (i > k) { hi = i - 1; }
            else if (i < k) { lo = i + 1; }
            else { return a[i]; }
        }
        return a[lo];
    }

    template<typename T>
    static bool less(T v, T w)
    {
        return v < w;
    }

    template<typename T>
    static void exch(std::vector<T>& a, int i, int j)
    {
        // std::swap(a[i], a[j]);
        T swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }

    template<typename T>
    static bool is_sorted(std::vector<T>& a)
    {
        return is_sorted(a, 0, static_cast<int>(a.size() - 1)); // narrow_cast
    }

    template<typename T>
    static bool is_sorted(std::vector<T>& a, int lo, int hi)
    {
        for (int i{lo + 1}; i <= hi; ++i) {
            if (less(a[i], a[i - 1])) { return false; }
        }
        return true;
    }

    template<typename T>
    static void show(std::vector<T>& a)
    {
        for (int i{0}; i < a.size(); ++i) {
            Std_out::print_line(a[i]);
        }
    }
};

#endif // QUICKSORT_H
