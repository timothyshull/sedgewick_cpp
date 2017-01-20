#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>
#include "utility.h"
#include "Std_out.h"

namespace Mergesort {
    template<typename T>
    static void sort(std::vector<T>& a, std::vector<T>& aux, int lo, int hi);

    template<typename T>
    static void sort(std::vector<T>& a);

    template<typename T>
    static bool less(T& v, T& w);

    template<typename T>
    static bool is_sorted(std::vector<T>& a);

    template<typename T>
    static bool is_sorted(std::vector<T>& a, int lo, int hi);

    template<typename T>
    static void merge(std::vector<T>& a, std::vector<int>& index, std::vector<int>& aux, int lo, int mid, int hi);

    template<typename T>
    static void merge(std::vector<T>& a, std::vector<T>& aux, int lo, int mid, int hi)
    {
        utility::assert(is_sorted(a, lo, mid), "Mergesort is_sorted check failed for lo to mid");
        utility::assert(is_sorted(a, mid + 1, hi), "Mergesort is_sorted check failed for mid + 1 to hi");

        for (int k = lo; k <= hi; k++) {
            aux[k] = a[k];
        }

        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; k++) {
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

        utility::assert(is_sorted(a, lo, hi), "Mergesort is_sorted check failed");
    }

    template<typename T>
    static void sort(std::vector<T>& a, std::vector<T>& aux, int lo, int hi)
    {
        if (hi <= lo) {
            return;
        }
        int mid = lo + (hi - lo) / 2;
        sort(a, aux, lo, mid);
        sort(a, aux, mid + 1, hi);
        merge(a, aux, lo, mid, hi);
    }

    template<typename T>
    static void sort(std::vector<T>& a)
    {
        std::vector<T> aux{};
        aux.reserve(a.size());
        sort(a, aux, 0, a.size() - 1);
        utility::assert(is_sorted(a), "Mergesort is_sorted check failed");
    }

    template<typename T>
    static bool less(T& v, T& w)
    {
        return v < w;
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
            if (less(a[i], a[i - 1])) {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    static void merge(std::vector<T>& a, std::vector<int>& index, std::vector<int>& aux, int lo, int mid, int hi)
    {
        for (int k = lo; k <= hi; k++) {
            aux[k] = index[k];
        }

        int i = lo;
        int j = mid + 1;
        for (int k = lo; k <= hi; k++) {
            if (i > mid) {
                index[k] = aux[j++];
            } else if (j > hi) {
                index[k] = aux[i++];
            } else if (less(a[aux[j]], a[aux[i]])) {
                index[k] = aux[j++];
            } else {
                index[k] = aux[i++];
            }
        }
    }

    template<typename T>
    static std::vector<int>& index_sort(std::vector<T>& a)
    {
        int n = a.size();
        std::vector<int> index{};
        index.reserve(static_cast<std::vector<int>::size_type>(n));
        for (int i = 0; i < n; ++i) {
            index[i] = i;
        }

        std::vector<int> aux{};
        aux.reserve(static_cast<std::vector<int>::size_type>(n));
        sort(a, index, aux, 0, n - 1);
        return index;
    }

    template<typename T>
    static void sort(std::vector<T>& a, std::vector<int>& index, std::vector<int>& aux, int lo, int hi)
    {
        if (hi <= lo) {
            return;
        }
        int mid = lo + (hi - lo) / 2;
        sort(a, index, aux, lo, mid);
        sort(a, index, aux, mid + 1, hi);
        merge(a, index, aux, lo, mid, hi);
    }

    template<typename T>
    static void show(std::vector<T>& a)
    {
        for (int i = 0; i < a.size(); ++i) {
            Std_out::print_line(a[i]);
        }
    }
};

#endif // MERGE_SORT_H
