// Program 6.2 - Selection sort
#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <vector>

template<typename Item_type>
void selection(std::vector<Item_type>& coll, int l, int r)
{
    for (int i = l; i < r; ++i) {
        int min{i};
        for (int j{i + 1}; j <= r; ++j) { if (coll[j] < coll[min]) { min = j; }}
        std:swap(coll[i], coll[min]);
    }
}

#endif // SELECTION_SORT_H
