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

template<typename Item_t>
void bucket_sort(std::vector<Item_t>& coll)
{
    if (coll.size() == 0) { return; }

    auto result = std::minmax_element(coll.begin(), coll.end());
    Item_t min{*result.first};
    Item_t max{*result.second};

    if (max == min) { return; }

    std::vector<std::vector<Item_t>> buckets(((max - min) / coll.size() + 1), std::vector<Item_t>{});

    for (auto e : coll) { buckets[(e - min) / buckets.size()].emplace_back(e); }

    coll.clear();
    for (auto v : buckets) {
        std::sort(v.begin(), v.end());
        coll.insert(coll.end(), v.begin(), v.end());
    }
}

// does extra work if bucket_size is greater than max - min
template<typename Item_t>
void bucket_sort(std::vector<Item_t>& coll, int bucket_size)
{
    if (coll.size() == 0 || bucket_size <= 0) { return; }

    auto result = std::minmax_element(coll.begin(), coll.end());
    Item_t min{*result.first};
    Item_t max{*result.second};

    if (max == min) { return; }

    std::vector<std::vector<Item_t>> buckets(
            static_cast<typename std::vector<std::vector<Item_t>>::size_type>((max - min) / bucket_size + 1),
            std::vector<Item_t>{}
    );

    for (auto e : coll) { buckets[(e - min) / bucket_size].emplace_back(e); }

    coll.clear();
    for (auto v : buckets) {
        std::sort(v.begin(), v.end());
        coll.insert(coll.end(), v.begin(), v.end());
    }
}

#endif // BUCKET_SORT_H
