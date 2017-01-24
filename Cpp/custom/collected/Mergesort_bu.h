#ifndef MERGESORT_BU_H
#define MERGESORT_BU_H

#include "utility.h"
#include "Std_out.h"

namespace Mergesort_bu {
    template<typename T>
    static void merge(std::vector<T>& a, std::vector<T>& aux, int lo, int mid, int hi)
    {
        for (int k = lo; k <= hi; ++k) {
            aux[k] = a[k];
        }

        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; ++k) {
            if (i > mid) {
                a[k] = aux[j++];
            } else if (j > hi) {
                a[k] = aux[i++];
            } else if (less(aux[j], aux[i])) {
                a[k] = aux[j++];
            } else {
                a[k] = aux[i++];
            }
        }
    }

    template<typename T>
    static void sort(std::vector<T>& a)
    {
        int n = a.size();
        std::vector<T> aux{};
        aux.reserve(a.size());
        for (int len = 1; len < n; len *= 2) {
            for (int lo = 0; lo < n - len; lo += len + len) {
                int mid = lo + len - 1;
                int hi = std::min<T>(lo + len + len - 1, n - 1);
                merge(a, aux, lo, mid, hi);
            }
        }
        utility::assert(is_sorted(a), "Mergesort_bu is_sorted check failed");
    }

    template<typename T>
    static bool less(T& v, T& w)
    {
        return v < w;
    }

    template<typename T>
    static bool is_sorted(std::vector<T>& a)
    {
        for (int i = 1; i < a.size(); ++i) {
            if (less(a[i], a[i - 1])) {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    static void show(std::vector<T>& a)
    {
        for (int i = 0; i < a.size(); ++i) {
            Std_out::print_line(a[i]);
        }
    }
};

#endif // MERGESORT_BU_H
