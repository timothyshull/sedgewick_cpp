#ifndef COLLECTED_HEAPSORT_H
#define COLLECTED_HEAPSORT_H

#include <vector>


// TODO: check this
template<typename Item_type>
void fix_down(std::vector<Item_type>& coll, int k, int n) // aka sink
{
    while (2 * k <= n) {
        int j = 2 * k;
        if (j < n && coll[j] < coll[j + 1]) { ++j; }
        if (!(coll[k] < coll[j])) { break; }
        std::swap(coll[k], coll[j]);
        k = j;
    }
}

template<typename Item_type>
void heapsort(std::vector<Item_type>& coll, int l, int r)
{
    int k;
    auto n = r - l + 1;
    // Item_type* pq = coll + l - 1;
    for (k = n / 2; k >= 1; k--) {
        fix_down(coll, k, n);
    }
    while (n > 1) {
        std::swap(coll[1], coll[n]);
        fix_down(coll, 1, --n);
    }
}

#endif // COLLECTED_HEAPSORT_H
