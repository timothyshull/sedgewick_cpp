#ifndef MERGESORT_X_H
#define MERGESORT_X_H

#include "utility.h"
#include "Std_out.h"

namespace Mergesort_x {
    static const int cutoff = 7;

    template<typename T>
    static void merge(std::vector<T>& src, std::vector<T>& dst, int lo, int mid, int hi)
    {
        utility::assert(is_sorted(src, lo, mid), "Mergesort_x is_sorted check failed for lo to mid");
        utility::assert(is_sorted(src, mid + 1, hi), "Mergesort_x is_sorted check failed for mid + 1 to hi");

        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; k++) {
            if (i > mid) { dst[k] = src[j++]; }
            else if (j > hi) { dst[k] = src[i++]; }
            else if (less(src[j], src[i])) {
                dst[k] = src[j++];
            } else { dst[k] = src[i++]; }
        }

        utility::assert(is_sorted(dst, lo, hi), "Mergesort_x is_sorted check failed");
    }

    template<typename T>
    static void sort(std::vector<T>& src, std::vector<T>& dst, int lo, int hi)
    {
        if (hi <= lo + cutoff) {
            insertion_sort(dst, lo, hi);
            return;
        }
        int mid = lo + (hi - lo) / 2;
        sort(dst, src, lo, mid);
        sort(dst, src, mid + 1, hi);

        // if (!less(src[mid+1], src[mid])) {
        //    for (int i = lo; i <= hi; i++) dst[i] = src[i];
        //    return;
        // }

        // using System.arraycopy() is a bit faster than the above loop
        if (!less(src[mid + 1], src[mid])) {
            System.arraycopy(src, lo, dst, lo, hi - lo + 1);
            return;
        }

        merge(src, dst, lo, mid, hi);
    }

    template<typename T>
    static void sort(std::vector<T>& a)
    {
        std::vector<T> aux{a};
        sort(aux, a, 0, a.size() - 1);
        utility::assert(is_sorted(a), "Mergesort_x is_sorted check failed");
    }

    template<typename T>
    static void insertion_sort(std::vector<T>& a, int lo, int hi)
    {
        for (int i = lo; i <= hi; i++) {
            for (int j = i; j > lo && less(a[j], a[j - 1]); j--) {
                exch(a, j, j - 1);
            }
        }
    }

    template<typename T>
    static void exch(std::vector<T>& a, int i, int j)
    {
        T swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }

    template<typename T>
    static bool less(T& a, T& b)
    {
        return a < b;
    }

    static bool less(T& a, T& b, Comparator comparator)
    {
        return comparator.compare(a, b) < 0;
    }

    template<typename T>
    static void sort(std::vector<T>& a, Comparator comparator)
    {
        std::vector<T> aux{a};
        sort(aux, a, 0, a.size() - 1, comparator);
        utility::assert(is_sorted(a, comparator);
    }

    template<typename T>
    static void merge(std::vector<T>& src, std::vector<T>& dst, int lo, int mid, int hi, Comparator comparator)
    {
        utility::assert(is_sorted(src, lo, mid, comparator), "Mergesort_x is_sorted check failed for lo to mid");
        utility::assert(is_sorted(src, mid + 1, hi, comparator), "Mergesort_x is_sorted check failed for mid + 1 to hi");

        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; k++) {
            if (i > mid) { dst[k] = src[j++]; }
            else if (j > hi) { dst[k] = src[i++]; }
            else if (less(src[j], src[i], comparator)) { dst[k] = src[j++]; }
            else { dst[k] = src[i++]; }
        }

        utility::assert(is_sorted(dst, lo, hi, comparator), "Mergesort_x is_sorted check failed");
    }

    template<typename T>
    static void sort(std::vector<T>& src, std::vector<T>& dst, int lo, int hi, Comparator comparator)
    {
        if (hi <= lo + cutoff) {
            insertion_sort(dst, lo, hi, comparator);
            return;
        }
        int mid = lo + (hi - lo) / 2;
        sort(dst, src, lo, mid, comparator);
        sort(dst, src, mid + 1, hi, comparator);

        // using System.arraycopy() is a bit faster than the above loop
        if (!less(src[mid + 1], src[mid], comparator)) {
            System.arraycopy(src, lo, dst, lo, hi - lo + 1);
            return;
        }

        merge(src, dst, lo, mid, hi, comparator);
    }

    template<typename T>
    static void insertion_sort(std::vector<T>& a, int lo, int hi, Comparator comparator)
    {
        for (int i = lo; i <= hi; i++) {
            for (int j = i; j > lo && less(a[j], a[j - 1], comparator); j--) {
                exch(a, j, j - 1);
            }
        }
    }

    template<typename T>
    static bool is_sorted(std::vector<T>& a)
    {
        return is_sorted(a, 0, a.size() - 1);
    }

    template<typename T>
    static bool is_sorted(std::vector<T>& a, int lo, int hi)
    {
        for (int i = lo + 1; i <= hi; i++) {
            if (less(a[i], a[i - 1])) { return false; }
        }
        return true;
    }

    template<typename T>
    static bool is_sorted(std::vector<T>& a, Comparator comparator)
    {
        return is_sorted(a, 0, a.size() - 1, comparator);
    }

    template<typename T>
    static bool is_sorted(std::vector<T>& a, int lo, int hi, Comparator comparator)
    {
        for (int i = lo + 1; i <= hi; i++) {
            if (less(a[i], a[i - 1], comparator)) { return false; }
        }
        return true;
    }

    template<typename T>
    static void show(std::vector<T>& a)
    {
        for (int i = 0; i < a.size(); i++) {
            Std_out::print_line(a[i]);
        }
    }
};

#endif // MERGESORT_X_H
