#ifndef RESIZING_ARRAY_STACK_H
#define RESIZING_ARRAY_STACK_H

#include <vector>
#include "utility.h"

template<typename T>
class Resizing_array_stack {
public:
    using Iterator_type = typename std::vector<T>::iterator;

    Resizing_array_stack()
            : _stack(static_cast<std::vector<T>::size_type>(2)),
              _size{2} {}

    inline bool is_empty() const noexcept { return _size == 0; }

    inline int size() const noexcept { return _size; }

    void push(T& item)
    {
        if (_size == _stack.size()) { resize(2 * _stack.size()); }
        _stack[_size++] = item;
    }

    void push(T&& item)
    {
        if (_size == _stack.size()) { resize(2 * _stack.size()); }
        _stack[_size++] = item;
    }

    T pop()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Stack underflow"}; }
        T item = _stack[_size - 1];
        _stack[_size - 1] = 0;
        --_size;
        if (_size > 0 && _size == _stack.size() / 4) { resize(_stack.size() / 2); }
        return item;
    }

    T peek()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Stack underflow"}; }
        return _stack[_size - 1];
    }

private:
    std::vector<T> _stack;
    int _size;

    void resize(std::size_t capacity)
    {
        utility::alg_assert(capacity >= _size, "Resizing_array_queue resize called with capacity less than current size");
        utility::alg_assert(capacity < _stack.max_size(), "Resizing_array_queue resize called with capacity greater than or equal to the max size");
        _stack.reserve(capacity);
    }
};

#endif // RESIZING_ARRAY_STACK_H
