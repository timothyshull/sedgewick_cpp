// Program 6.3 - Insertion sort
#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <vector>

template<typename Item_t>
void insertion(std::vector<Item_t>& coll, int l, int r)
{
    int i;
    for (i = r; i > l; --i) {
        if (coll[i] < coll[i - 1]) { std::swap(coll[i - 1], coll[i]); }
    }
    for (i = l + 2; i <= r; ++i) {
        auto j = i;
        Item_t v = coll[i];
        while (v < coll[j - 1]) {
            coll[j] = coll[j - 1];
            --j;
        }
        coll[j] = v;
    }
}

#endif // INSERTION_SORT_H
