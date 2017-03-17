#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <vector>
#include "Std_out.h"

class Bubblesort {
public:
    template<typename T>
    static void sort(std::vector<T>& a)
    {
        int n{static_cast<int>(a.size())}; // narrow_cast
        for (int i = 0; i < n; ++i) {
            int exchanges = 0;
            for (int j = n - 1; j > i; j--) {
                if (less(a[j], a[j - 1])) {
                    exch(a, j, j - 1);
                    exchanges++;
                }
            }
            if (exchanges == 0) { break; }
        }
    }

    template<typename T>
    static void show(std::vector<T>& a)
    {
        for (int i{0}; i < a.size(); ++i) {
            Std_out::print_line(a[i]);
        }
    }

private:
    template<typename T>
    inline static bool less(T& v, T& w) { return v < w; }

    template<typename T>
    static void exch(std::vector<T>& a, int i, int j)
    {
        T swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }
};

#endif // BUBBLE_SORT_H
