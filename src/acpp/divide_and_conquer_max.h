// Program 5.6 - Divide-and-conquer to find the maximum
#ifndef DIVIDE_AND_CONQUER_MAX_H
#define DIVIDE_AND_CONQUER_MAX_H

#include <vector>

template<typename Item_type>
Item_type max(std::vector<Item_type>& coll, int l, int r)
{
    if (l == r) { return coll[l]; }
    auto m = (l + r) / 2;
    Item_type u{max(coll, l, m)};
    Item_type v{max(coll, m + 1, r)};
    if (u > v) { return u; } else { return v; }
}

#endif // DIVIDE_AND_CONQUER_MAX_H
