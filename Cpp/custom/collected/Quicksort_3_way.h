#ifndef QUICKSORT_3_WAY_H
#define QUICKSORT_3_WAY_H

#include <vector>
#include "utility.h"
#include "Std_random.h"
#include "Std_out.h"

namespace Quicksort_3_way {
    template<typename T>
    void sort(std::vector<T>& a, int lo, int hi);

    template<typename T>
    bool less(T v, T w);

    template<typename T>
    void exch(std::vector<T>& a, int i, int j);

    template<typename T>
    bool is_sorted(std::vector<T>& a);

    template<typename T>
    bool is_sorted(std::vector<T>& a, int lo, int hi);

    template<typename T>
    void sort(std::vector<T>& a)
    {
        Std_random::shuffle(a);
        sort(a, 0, a.size() - 1);
        utility::assert(is_sorted(a), "Quicksort_3_way is_sorted check failed");
    }

    template<typename T>
    void sort(std::vector<T>& a, int lo, int hi)
    {
        if (hi <= lo) { return; }
        int lt = lo, gt = hi;
        T v = a[lo];
        int i = lo;
        while (i <= gt) {
            if (a[i] < v) { exch(a, lt++, i++); }
            else if (a[i] > v) { exch(a, i, gt--); }
            else { ++i; }
        }

        sort(a, lo, lt - 1);
        sort(a, gt + 1, hi);
        utility::assert(is_sorted(a, lo, hi), "Quicksort_3_way is_sorted check failed");
    }

    template<typename T>
    bool less(T v, T w)
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

    template<typename T>
    void show(std::vector<T>& a)
    {
        for (int i = 0; i < a.size(); ++i) {
            Std_out::print_line(a[i]);
        }
    }
};

#endif // QUICKSORT_3_WAY_H
