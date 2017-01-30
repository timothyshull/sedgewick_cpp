#ifndef RESIZING_ARRAY_BAG_H
#define RESIZING_ARRAY_BAG_H

#include <vector>
#include "utility.h"

template<typename T>
class Resizing_array_bag {
public:
    using Iterator_type = typename std::vector<T>::iterator;

    Resizing_array_bag()
            : _bag(static_cast<std::vector<T>::size_type>(2)),
              _size{2} {}

    inline bool is_empty() const noexcept { return _size == 0; }

    inline int size() const noexcept { return _size; }

    void add(T& item)
    {
        if (_size == _bag.size()) { _resize(2 * _bag.size()); }
        _bag[_size++] = item;
    }

    void add(T&& item)
    {
        if (_size == _bag.size()) { _resize(2 * _bag.size()); }
        _bag[_size++] = item;
    }

    inline Iterator_type begin() { return _bag.begin(); }

    inline Iterator_type end() { return _bag.end(); }

private:
    std::vector<T> _bag;
    int _size;

    void _resize(std::size_t capacity)
    {
        utility::alg_assert(capacity >= _size, "Resizing_array_bag resize called with capacity less than current size");
        utility::alg_assert(capacity < _bag.max_size(), "Resizing_array_bag resize called with capacity greater than or equal to the max size");
        _bag.reserve(capacity);
    }
};

#endif // RESIZING_ARRAY_BAG_H
