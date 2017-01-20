#ifndef INSERTION_H
#define INSERTION_H

#include <vector>
#include "utility.h"
#include "Std_out.h"

namespace Insertion_sort {
    static void exch(std::vector<int> a, int i, int j);

    template<typename T, typename Comparator = std::less<T>>
    static bool less(T& v, T& w);

    template<typename T>
    static void exch(std::vector<T>& a, int i, int j);

    template<typename T, typename Comparator = std::less<T>>
    static bool is_sorted(std::vector<T>& a);

    template<typename T, typename Comparator = std::less<T>>
    static bool is_sorted(std::vector<T>& a, int lo, int hi);

    template<typename T, typename Comparator = std::less<T>>
    static void sort(std::vector<T>& a)
    {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            for (int j = i; j > 0 && less<T, Comparator>(a[j], a[j - 1]); j--) {
                exch(a, j, j - 1);
            }
            // utility::assert(is_sorted<T, Comparator>(a, 0, i), "The Insertion_sort is_sorted check failed before completing");
        }
        utility::assert(is_sorted<T, Comparator>(a), "The Insertion_sort is_sorted check failed");
    }

    template<typename T, typename Comparator>
    static void sort(std::vector<T>& a, int lo, int hi)
    {
        for (int i = lo; i <= hi; i++) {
            for (int j = i; j > lo && less<T, Comparator>(a[j], a[j - 1]); j--) {
                exch(a, j, j - 1);
            }
            // utility::assert(is_sorted<T, Comparator>(a, 0, i), "The Insertion_sort is_sorted check failed before completing");
        }
        utility::assert(is_sorted<T, Comparator>(a, lo, hi), "The Insertion_sort is_sorted check failed");
    }

    template<typename T>
    static std::vector<int> index_sort(std::vector<T>& a)
    {
        int n = a.size();
        std::vector<int> index{};
        index.reserve(n);
        for (int i = 0; i < n; i++) {
            index[i] = i;
        }

        for (int i = 0; i < n; i++) {
            for (int j = i; j > 0 && less(a[index[j]], a[index[j - 1]]); j--) {
                exch(index, j, j - 1);
            }
        }

        return index;
    }

    template<typename T>
    static bool less(T& v, T& w)
    {
        return v < w;
    }

    template<typename T, typename Comparator>
    static bool less(T& v, T& w)
    {
        return Comparator{}(v, w);
    }

    template<typename T>
    static void exch(std::vector<T>& a, int i, int j)
    {
        T swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }

    template<typename T, typename Comparator>
    static bool is_sorted(std::vector<T>& a)
    {
        return is_sorted<T, Comparator>(a, 0, a.size() - 1);
    }

    template<typename T, typename Comparator>
    static bool is_sorted(std::vector<T>& a, int lo, int hi)
    {
        for (int i = lo + 1; i <= hi; i++) {
            if (less<T, Comparator>(a[i], a[i - 1])) {
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

#endif // INSERTION_H
