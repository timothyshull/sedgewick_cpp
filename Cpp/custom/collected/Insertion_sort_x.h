#ifndef INSERTION_X_H
#define INSERTION_X_H

#include <vector>
#include "utility.h"
#include "Std_out.h"

namespace Insertion_sort_x {
    template<typename T>
    static void exch(std::vector<T>& a, int i, int j);

    template<typename T>
    static bool is_sorted(std::vector<T>& a);

    template<typename T>
    static bool less(T v, T w);

    template<typename T>
    static void sort(std::vector<T>& a)
    {
        int n = a.size();

        int exchanges = 0;
        for (int i = n - 1; i > 0; i--) {
            if (less(a[i], a[i - 1])) {
                exch<T>(a, i, i - 1);
                exchanges++;
            }
        }
        if (exchanges == 0) { return; }

        for (int i = 2; i < n; ++i) {
            T v = a[i];
            int j = i;
            while (less(v, a[j - 1])) {
                a[j] = a[j - 1];
                j--;
            }
            a[j] = v;
        }

        utility::assert(is_sorted(a), "Insertion_sort_x is_sorted check failed");
    }

    template<typename T>
    static bool less(T v, T w)
    {
        return v < w;
    }

    template<typename T>
    static void exch(std::vector<T>& a, int i, int j)
    {
        T swap = a[i];
        a[i] = a[j];
        a[j] = swap;
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

#endif // INSERTION_X_H
