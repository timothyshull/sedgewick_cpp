#ifndef BINARY_INSERTION_H
#define BINARY_INSERTION_H

#include <vector>
#include "utility.h"
#include "Std_out.h"

namespace Binary_insertion_sort {
    template<typename T>
    static inline bool less(T& v, T& w);

    template<typename T>
    static bool is_sorted(std::vector<T>& a);

    template<typename T>
    static bool is_sorted(std::vector<T>& a, int lo, int hi);

    template<typename T>
    static void sort(std::vector<T>& a)
    {
        int n{static_cast<int>(a.size())};
        for (int i{1}; i < n; ++i) {
            T v = a[i];
            int lo = 0, hi = i;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                if (less(v, a[mid])) { hi = mid; }
                else { lo = mid + 1; }
            }

            for (int j{i}; j > lo; --j) {
                a[j] = a[j - 1];
            }
            a[lo] = v;
        }
        utility::alg_assert(is_sorted(a), "The Binary_insertion_sort is_sorted _check failed");
    }

    template<typename T>
    static inline bool less(T& v, T& w)
    {
        return v < w;
    }

    template<typename T>
    static bool is_sorted(std::vector<T>& a)
    {
        return is_sorted(a, 0, static_cast<int>(a.size()) - 1);
    }

    template<typename T>
    static bool is_sorted(std::vector<T>& a, int lo, int hi)
    {
        for (int i{lo + 1}; i <= hi; ++i) {
            if (less(a[i], a[i - 1])) {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    static void show(std::vector<T>& a)
    {
        for (auto t : a) {
            Std_out::print_line(t);
        }
    }
};

#endif // BINARY_INSERTION_H
