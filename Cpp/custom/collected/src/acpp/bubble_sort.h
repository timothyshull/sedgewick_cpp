// Program 6.4 - Bubble sort
#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <vector>

template<typename Item_type>
void bubble(std::vector<Item_type>& coll, int l, int r)
{
    for (int i{l}; i < r; ++i) {
        for (int j{r}; j > i; --j) {
            if (coll[j] < coll[j - 1]) { std::swap(coll[j - 1], coll[j]); }
        }
    }
}

#endif // BUBBLE_SORT_H
