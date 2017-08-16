#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <sstream>
#include <gsl/gsl_util>

#include "sort_utility.h"
#include "utility.h"

namespace Heap_sort {
    using namespace Sort_utility;

    template<typename Item_t>
    static void sink(std::vector<Item_t> &pq, int k, int n)
    {
        while (2 * k <= n) {
            auto j = 2 * k;
            if (j < n && pq[j] < pq[j + 1]) {
                ++j;
            }
            if (pq[j] < pq[k]) {
                break;
            }
            std::swap(pq[k], pq[j]);
            k = j;
        }
    }

    // NOTE: prepends default constructed element to input vector to handle indices simplification
    // not the best solution for real-world use
    template<typename Item_t>
    void sort(std::vector<Item_t> &pq)
    {
        pq.insert(pq.begin(), Item_t{});
        auto n = gsl::narrow_cast<int>(pq.size() - 1); // have to use size - 1
        for (auto k = n / 2; k >= 1; --k) {
            sink(pq, k, n);
        }
        while (n > 1) {
            std::swap(pq[1], pq[n]);
            --n;
            sink(pq, 1, n);
        }
        pq.erase(pq.begin());
        utility::alg_assert(std::is_sorted(pq.begin(), pq.end()), "The Heap_sort is_sorted check failed");

    }
};

#endif // HEAP_H
