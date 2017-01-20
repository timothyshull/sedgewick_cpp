#ifndef COLLECTED_SELECTION_SORT_H
#define COLLECTED_SELECTION_SORT_H

#include "utility.h"
#include "Std_out.h"

namespace Selection_sort {
    template<typename T, typename Comparator = std::less>
    void sort(std::vector<T>& a);

    template<typename T>
    bool less(T& v, T& w);

    template<typename T, typename Comparator = std::less>
    bool less(T& v, T& w);

    template<typename T>
    void exch(std::vector<T>& a, int i, int j);

    template<typename T>
    bool is_sorted(std::vector<T>& a);

    template<typename T>
    bool is_sorted(std::vector<T>& a, int lo, int hi);

    template<typename T, typename Comparator = std::less>
    bool is_sorted(std::vector<T>& a);

    template<typename T, typename Comparator = std::less>
    bool is_sorted(std::vector<T>& a, int lo, int hi);

    // causes ambiguous template resolution
    // template<typename T>
    // void sort(std::vector<T>& a)
    // {
    //     int n = a.size();
    //     for (int i = 0; i < n; ++i) {
    //         int min = i;
    //         for (int j = i + 1; j < n; ++j) {
    //             if (less(a[j], a[min])) { min = j; }
    //         }
    //         exch(a, i, min);
    //         utility::assert(is_sorted(a, 0, i), "Selection_sort is_sorted range check failed");
    //     }
    //     utility::assert(is_sorted(a), "Selection_sort is_sorted check failed");
    // }

    template<typename T, typename Comparator>
    void sort(std::vector<T>& a)
    {
        int n = a.size();
        for (int i = 0; i < n; ++i) {
            int min = i;
            for (int j = i + 1; j < n; ++j) {
                if (less<T, Comparator>(a[j], a[min])) { min = j; }
            }
            exch(a, i, min);
            utility::assert(is_sorted<T, Comparator>(a, 0, i), "Selection_sort is_sorted range check failed");
        }
        utility::assert(is_sorted<T, Comparator>(a), "Selection_sort is_sorted check failed");
    }

    template<typename T>
    bool less(T& v, T& w)
    {
        return v < w;
    }

    template<typename T, typename Comparator>
    bool less(T& v, T& w)
    {
        return Comparator{}(v, w);
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
        return is_sorted(a, 0, a.size() - 1);
    }

    template<typename T>
    bool is_sorted(std::vector<T>& a, int lo, int hi)
    {
        for (int i = lo + 1; i <= hi; ++i) {
            if (less(a[i], a[i - 1])) { return false; }
        }
        return true;
    }

    template<typename T, typename Comparator>
    bool is_sorted(std::vector<T>& a)
    {
        return is_sorted<T, Comparator>(a, 0, a.size() - 1);
    }

    template<typename T, typename Comparator>
    bool is_sorted(std::vector<T>& a, int lo, int hi)
    {
        for (int i = lo + 1; i <= hi; ++i) {
            if (less<T, Comparator>(a[i], a[i - 1])) {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    void show(std::vector<T>& a)
    {
        for (auto t : a) {
            Std_out::print_line(t);
        }
    }
};

#endif // COLLECTED_SELECTION_SORT_H
