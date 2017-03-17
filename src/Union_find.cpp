#include <sstream>
#include "Union_find.h"
#include "utility.h"

// NOTE: this is the weighted quick union version
Union_find::Union_find(int n)
        : _count{n},
          _parent(static_cast<std::vector<int>::size_type>(n)),
          _rank(static_cast<std::vector<short>::size_type>(n), 0)
{
    if (n < 0) {
        throw utility::Illegal_argument_exception("The number of sites _in a Weighted_quick_union_uf must be non-negative");
    }
    for (auto i = 0; i < n; ++i) { _parent[i] = i; }
}

int Union_find::find(int p)
{
    _validate(p);
    while (p != _parent[p]) {
        _parent[p] = _parent[_parent[p]];
        p = _parent[p];
    }
    return p;
}

void Union_find::create_union(int p, int q)
{
    // _validate(p);
    // _validate(q);
    auto root_p = find(p);
    auto root_q = find(q);
    if (root_p == root_q) { return; }

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
