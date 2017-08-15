// Program 4.11 - Equivalence relations ADT implementation
#include "Union_find.h"

Union_find::Union_find(std::size_t size)
        : _id(size),
          _size(size)
{
    for (auto i = 0; i < size; ++i) {
        _id[i] = i;
        _size[i] = 1;
    }
}

void Union_find::unite(int p, int q)
{
    auto i = _find(p);
    auto j = _find(q);
    if (i == j) { return; }
    if (_size[i] < _size[j]) {
        _id[i] = j;
        _size[j] += _size[i];
    } else {
        _id[j] = i;
        _size[i] += _size[j];
    }
}

int Union_find::_find(int x) const
{
    while (x != _id[x]) { x = _id[x]; }
    return x;
}
