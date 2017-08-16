// Program 5.6 - Divide-and-conquer to find the maximum
#ifndef DIVIDE_AND_CONQUER_MAX_H
#define DIVIDE_AND_CONQUER_MAX_H

#include <vector>

template<typename Item_t>
Item_t max(std::vector<Item_t>& coll, int l, int r)
{
    if (l == r) { return coll[l]; }
    auto m = (l + r) / 2;
    Item_t u{max(coll, l, m)};
    Item_t v{max(coll, m + 1, r)};
    if (u > v) { return u; } else { return v; }
}

#endif // DIVIDE_AND_CONQUER_MAX_H
