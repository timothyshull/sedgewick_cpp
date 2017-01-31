#include "Quick_union_uf.h"
#include "utility.h"

Quick_union_uf::Quick_union_uf(int n)
        : _count{n},
          _parent(static_cast<std::vector<int>::size_type>(n))
{
    for (int i{0}; i < n; ++i) {
        _parent[i] = i;
    }
}

int Quick_union_uf::find(int p)
{
    _validate(p);
    while (p != _parent[p]) {
        p = _parent[p];
    }
    return p;
}

void Quick_union_uf::create_union(int p, int q)
{
    int rootP = find(p);
    int rootQ = find(q);
    if (rootP == rootQ) { return; }
    _parent[rootP] = rootQ;
    _count--;
}

void Quick_union_uf::_validate(int p)
{
    auto n = _parent.size();
    if (p < 0 || p >= n) {
        throw utility::Index_out_of_bounds_exception{"index " + std::to_string(p) + " is not between 0 and " + std::to_string(n - 1)};
    }
}
