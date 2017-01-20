#ifndef QUICKSORT_X_H
#define QUICKSORT_X_H

#include "Std_out.h"

namespace Quicksort_x {
    static const int insertion_sort_cutoff = 8;

    static const int median_of_3_cutoff = 40;

    template<typename T>
    void sort(std::vector<T>& a, int lo, int hi);

    template<typename T>
    void insertion_sort(std::vector<T>& a, int lo, int hi);

    template<typename T>
    int median_of_3(std::vector<T>& a, int i, int j, int k);

    template<typename T>
    bool less(T& v, T& w);

    template<typename T>
    bool eq(T& v, T& w);

    template<typename T>
    void exch(std::vector<T>& a, int i, int j);

    template<typename T>
    bool is_sorted(std::vector<T>& a);

    template<typename T>
    void sort(std::vector<T>& a)
    {
        sort(a, 0, a.size() - 1);
    }

    template<typename T>
    void sort(std::vector<T>& a, int lo, int hi)
    {
        int n = hi - lo + 1;

        if (n <= insertion_sort_cutoff) {
            insertion_sort(a, lo, hi);
            return;
        } else if (n <= median_of_3_cutoff) {
            int m = median_of_3(a, lo, lo + n / 2, hi);
            exch(a, m, lo);
        } else {
            int eps = n / 8;
            int mid = lo + n / 2;
            int m1 = median_of_3(a, lo, lo + eps, lo + eps + eps);
            int m2 = median_of_3(a, mid - eps, mid, mid + eps);
            int m3 = median_of_3(a, hi - eps - eps, hi - eps, hi);
            int ninther = median_of_3(a, m1, m2, m3);
            exch(a, ninther, lo);
        }

        int i = lo, j = hi + 1;
        int p = lo, q = hi + 1;
        T v = a[lo];
        while (true) {
            while (less(a[++i], v)) {
                if (i == hi) { break; }
            }
            while (less(v, a[--j])) {
                if (j == lo) { break; }
            }

            if (i == j && eq(a[i], v)) {
                exch(a, ++p, i);
            }
            if (i >= j) { break; }

            exch(a, i, j);
            if (eq(a[i], v)) { exch(a, ++p, i); }
            if (eq(a[j], v)) { exch(a, --q, j); }
        }

        i = j + 1;
        for (int k = lo; k <= p; ++k) {
            exch(a, k, j--);
        }
        for (int k = hi; k >= q; k--) {
            exch(a, k, i++);
        }

        sort(a, lo, j);
        sort(a, i, hi);
    }

    template<typename T>
    void insertion_sort(std::vector<T>& a, int lo, int hi)
    {
        for (int i = lo; i <= hi; ++i) {
            for (int j = i; j > lo && less(a[j], a[j - 1]); j--) {
                exch(a, j, j - 1);
            }
        }
    }

    template<typename T>
    int median_of_3(std::vector<T>& a, int i, int j, int k)
    {
        return (less(a[i], a[j]) ? (less(a[j], a[k]) ? j : less(a[i], a[k]) ? k : i) : (less(a[k], a[j]) ? j : less(a[k], a[i]) ? k : i));
    }

    template<typename T>
    bool less(T& v, T& w)
    {
        return v < w;
    }

    template<typename T>
    bool eq(T& v, T& w)
    {
        return v == w;
    }

    template<typename T>
    void exch(std::vector<T>& a, int i, int j)
    {
        T swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }

    template<typename T>
    bool is_sorted(std::vector<T>& a)
    {
        for (int i = 1; i < a.size(); ++i) {
            if (less(a[i], a[i - 1])) { return false; }
        }
        return true;
    }

    template<typename T>
    void show(std::vector<T>& a)
    {
        for (auto t: a) {
            Std_out::print_line(t);
        }
    }
};

#endif // QUICKSORT_X_H
