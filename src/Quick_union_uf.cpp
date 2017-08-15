#include "Quick_union_uf.h"
#include "utility.h"

Quick_union_uf::Quick_union_uf(int n)
        : _count{n},
          _parent(static_cast<std::vector<int>::size_type>(n))
{
    for (auto i = 0; i < n; ++i) {
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
    int root_p = find(p);
    int root_q = find(q);
    if (root_p == root_q) { return; }
    _parent[root_p] = root_q;
    _count--;
}

void Quick_union_uf::_validate(int p)
{
    auto n = _parent.size();
    if (p < 0 || p >= n) {
        throw utility::Index_out_of_bounds_exception{"index " + std::to_string(p) + " is not between 0 and " + std::to_string(n - 1)};
    }
}
