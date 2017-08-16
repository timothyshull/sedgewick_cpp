// Program 6.14 - In-place sort
#ifndef IN_PLACE_SORT_H
#define IN_PLACE_SORT_H

#include <vector>

template<typename Item_t, typename Index_type>
void in_place_sort(std::vector<Item_t>& data, std::vector<Index_type>& a, int size)
{
    for (auto i = 0; i < size; ++i) {
        Item_t v = data[i];
        int j;
        int k;
        for (k = i; a[k] != i; k = a[j], a[j] = j) {
            j = k;
            data[k] = data[a[k]];
        }
        data[k] = v;
        a[k] = k;
    }
}

#endif // IN_PLACE_SORT_H
