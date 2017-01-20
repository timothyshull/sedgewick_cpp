#ifndef SHELLSORT_H
#define SHELLSORT_H

#include "utility.h"
#include "Std_out.h"

namespace Shellsort {
    template<typename T>
    bool less(T& v, T& w);

    template<typename T>
    void exch(std::vector<T>& a, int i, int j);

    template<typename T>
    bool is_sorted(std::vector<T>& a);

    template<typename T>
    bool is_h_sorted(std::vector<T>& a, int h);

    template<typename T>
    void sort(std::vector<T>& a)
    {
        int n = a.size();

        // 3x+1 increment sequence:  1, 4, 13, 40, 121, 364, 1093, ...
        int h = 1;
        while (h < n / 3) { h = 3 * h + 1; }

        while (h >= 1) {
            // h-sort the array
            for (int i = h; i < n; ++i) {
                for (int j = i; j >= h && less(a[j], a[j - h]); j -= h) {
                    exch(a, j, j - h);
                }
            }
            utility::assert(is_h_sorted(a, h), "Shellsort is_h_sorted check failed");
            h /= 3;
        }
        utility::assert(is_sorted(a), "Shellsort is_sorted check failed");
    }

    template<typename T>
    bool less(T& v, T& w)
    {
        return v < w;
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
    bool is_h_sorted(std::vector<T>& a, int h)
    {
        for (int i = h; i < a.size(); ++i) {
            if (less(a[i], a[i - h])) { return false; }
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

#endif // SHELLSORT_H
