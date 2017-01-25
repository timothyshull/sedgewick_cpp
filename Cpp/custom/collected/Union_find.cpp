#include <sstream>
#include "Union_find.h"
#include "utility.h"

Union_find::Union_find(int n)
        : _count{n},
          _parent(static_cast<std::vector<int>::size_type>(n)),
          _rank(static_cast<std::vector<short>::size_type>(n))
{
    if (n < 0) {
        throw utility::Illegal_argument_exception("The number of sites in a Weighted_quick_union_uf must be non-negative");
    }
    for (int i{0}; i < n; ++i) {
        _parent[i] = i;
        _rank[i] = 0;
    }
}

int Union_find::find(int p) const
{
    _validate(p);
    while (p != _parent[p]) {
        _parent[p] = _parent[_parent[p]];
        p = _parent[p];
    }
    return p;
}

bool Union_find::connected(int p, int q) const
{
    return find(p) == find(q);
}

void Union_find::create_union(int p, int q)
{
    int root_p = find(p);
    int root_q = find(q);
    if (root_p == root_q) {
        return;
    }

    if (_rank[root_p] < _rank[root_q]) {
        _parent[root_p] = root_q;
    } else if (_rank[root_p] > _rank[root_q]) {
        _parent[root_q] = root_p;
    } else {
        _parent[root_q] = root_p;
        _rank[root_p]++;
    }
    --_count;
}

void Union_find::_validate(int p) const
{
    auto n = _parent.size();
    if (p < 0 || p >= n) {
        std::stringstream ss;
        ss << "Index " << p << " is not between 0 and " << (n - 1);
        throw utility::Index_out_of_bounds_exception(ss.str());
    }
}
