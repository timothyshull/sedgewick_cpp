#include "Quick_find_uf.h"
#include "utility.h"

Quick_find_uf::Quick_find_uf(int n)
        : _count{n},
          _id(static_cast<std::vector<int>::size_type>(n))
{
    for (int i{0}; i < n; ++i) {
        _id[i] = i;
    }
}

int Quick_find_uf::find(int p)
{
    _validate(p);
    return _id[p];
}

bool Quick_find_uf::connected(int p, int q)
{
    _validate(p);
    _validate(q);
    return _id[p] == _id[q];
}

void Quick_find_uf::create_union(int p, int q)
{
    _validate(p);
    _validate(q);
    int p_id = _id[p];
    int q_id = _id[q];

    if (p_id == q_id) { return; }

    for (int i{0}; i < _id.size(); ++i) {
        if (_id[i] == p_id) { _id[i] = q_id; }
    }
    --_count;
}

void Quick_find_uf::_validate(int p)
{
    auto n = _id.size();
    if (p < 0 || p >= n) {
        throw utility::Index_out_of_bounds_exception{"index " + std::to_string(p) + " is not between 0 and " + std::to_string(n - 1)};
    }
}
