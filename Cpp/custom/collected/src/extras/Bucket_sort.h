#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H

// from Cormen
// bucket_sort(a)
//     n = a.size
//     let b[0...n - 1] -> new array
//     for i = 0 to n - 1
//         create empty list b[i]
//     for i = 0 to n - 1
//         insert a[i] into b[na[i]]
//     for i = 0 to n - 1
//         sort list b[i] with insertion sort
//     concatenate lists b[0], b[1], ... b[n - 1] in order

#include <vector>

template<typename Item_type>
void bucket_sort(std::vector<Item_type>& coll)
{
    std::vector<std::vector<Item_type>> b(coll.size(), std::vector<Item_type>{});

    int b_idx;
    for (int i{0}; i < coll.size(); ++i) {
        b_idx = coll.size() * coll[i];
        b[b_idx].emplace_back(coll[i]);
    }

    for (auto v : b) { std::sort(v.begin(), v.end()); }

    coll.clear();
    for (auto v : b) { coll.insert(coll.end(), v.begin(), v.end()); }
}



#endif // BUCKET_SORT_H
