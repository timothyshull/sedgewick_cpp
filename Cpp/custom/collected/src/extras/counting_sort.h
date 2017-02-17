#ifndef COUNTING_SORT_H
#define COUNTING_SORT_H

#include <vector>

// from http://opendatastructures.org/ods-cpp/11_2_Counting_Sort_Radix_So.html
template<typename Item_type>
void counting_sort(std::vector<Item_type>& coll, int k)
{
    std::vector<Item_type> aux1(k, 0);
    for (int i{0}; i < coll.size(); ++i) { aux1[coll[i]]++; }
    for (int i{1}; i < k; i++) { aux1[i] += aux1[i - 1]; }

    std::vector<Item_type> aux2(coll.size());
    for (int i{static_cast<int>(coll.size() - 1)}; i >= 0; --i) {
        aux2[--aux1[coll[i]]] = coll[i];
    }
    coll = aux2;
}

#endif // COUNTING_SORT_H
