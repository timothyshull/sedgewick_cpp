#include "Weighted_quick_union_uf.h"
#include "utility.h"

Weighted_quick_union_uf::Weighted_quick_union_uf(int n)
        : _count{n},
          _parent(static_cast<std::vector<int>::size_type>(n)),
          _size(static_cast<std::vector<int>::size_type>(n))
{
    if (n < 0) {
        throw utility::Illegal_argument_exception{
                "The number of sites _in a Weighted_quick_union_uf must be non-negative"
        };
    }
    for (auto i = 0; i < n; ++i) {
        _parent[i] = i;
        _size[i] = i;
    }
}

int Weighted_quick_union_uf::find(int p) const
{
    _validate(p);
    while (p != _parent[p]) {
        p = _parent[p];
    }
    return p;
}

void Weighted_quick_union_uf::create_union(int p, int q)
{
    auto root_p = find(p);
    auto root_q = find(q);
    if (root_p == root_q) {
        return;
    }

    if (_size[root_p] < _size[root_q]) {
        _parent[root_p] = root_q;
        _size[root_q] += _size[root_p];
    } else {
        _parent[root_q] = root_p;
        _size[root_p] += _size[root_q];
    }
    --_count;
}

void Weighted_quick_union_uf::_validate(int p) const
{
    auto n = _parent.size();
    if (p < 0 || p >= n) {
        throw utility::Index_out_of_bounds_exception(
                "Index " + std::to_string(p) + " is not between 0 and " + std::to_string(n - 1)
        );
    }
}
