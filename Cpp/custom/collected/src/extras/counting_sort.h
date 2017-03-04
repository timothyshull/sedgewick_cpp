#ifndef COUNTING_SORT_H
#define COUNTING_SORT_H

#include <vector>

// from http://opendatastructures.org/ods-cpp/11_2_Counting_Sort_Radix_So.html
template<typename Item_type>
void counting_sort(std::vector<Item_type>& coll, int k)
{
    std::vector<Item_type> aux1(k, 0);
    for (auto e : coll) { ++aux1[e]; }
    for (int i{1}; i < k; i++) { aux1[i] += aux1[i - 1]; }

    std::vector<Item_type> aux2(coll.size());
    for (int i{static_cast<int>(coll.size() - 1)}; i >= 0; --i) {
        aux2[--aux1[coll[i]]] = coll[i];
    }
    coll = aux2;
}

// from https://probablydance.com/2016/12/02/investigating-radix-sort/
template<typename It, typename OutIt, typename ExtractKey>
void counting_sort(It begin, It end, OutIt out_begin, ExtractKey&& extract_key)
{
    size_t counts[256] = {};
    for (It it = begin; it != end; ++it) {
        ++counts[extract_key(*it)];
    }
    size_t total = 0;
    for (size_t& count : counts) {
        size_t old_count = count;
        count = total;
        total += old_count;
    }
    for (; begin != end; ++begin) {
        std::uint8_t key = extract_key(*begin);
        out_begin[counts[key]++] = std::move(*begin);
    }
}

#endif // COUNTING_SORT_H
