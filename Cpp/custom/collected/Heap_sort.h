#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <sstream>
#include "Std_out.h"

namespace Heap_sort {
    template<typename T>
    static void sink(std::vector<T>& pq, int k, int n);

    template<typename T>
    static bool less(T& v, T& w);

    template<typename T>
    static bool less(std::vector<T>& pq, int i, int j);

    template<typename T>
    static void exch(std::vector<T>& pq, int i, int j);

    template<typename T>
    static void sort(std::vector<T>& pq)
    {
        int n = static_cast<int>(pq.size());
        for (int k = n / 2; k >= 1; --k) {
            sink(pq, k, n);
        }
        while (n > 1) {
            exch(pq, 1, n);
            --n;
            sink(pq, 1, n);
        }
    }

    template<typename T>
    static void sink(std::vector<T>& pq, int k, int n)
    {
        while (2 * k <= n) {
            int j = 2 * k;
            if (j < n && less(pq, j, j + 1)) {
                ++j;
            }
            if (!less(pq, k, j)) {
                break;
            }
            exch(pq, k, j);
            k = j;
        }
    }

    template<typename T>
    static bool less(T& v, T& w)
    {
        return v < w;
    }

    template<typename T>
    static bool less(std::vector<T>& pq, int i, int j)
    {
        return pq[i - 1] < pq[j - 1];
    }

    template<typename T>
    static void exch(std::vector<T>& pq, int i, int j)
    {
        T tmp = pq[i - 1];
        pq[i - 1] = pq[j - 1];
        pq[j - 1] = tmp;
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

#endif // HEAP_H