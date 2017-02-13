// Program 4.7 - Array implementation of a pushdown stack
#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <cstddef>
#include <vector>

template<typename Item_type>
class Array_stack {
public:
    Array_stack() = default;

    ~Array_stack() = default;

    Array_stack(const Array_stack&) = default;

    Array_stack(Array_stack&&) = default;

    Array_stack& operator=(const Array_stack&) = default;

    explicit Array_stack(std::size_t max_elements) : _stack(max_elements), _size{0} {}

    inline bool empty() const noexcept { return _size == 0; }

    void push(Item_type& item) { _stack[_size++] = item; }

    void push(Item_type&& item) { _stack[_size++] = item; }

    Item_type pop() { return _stack[--_size]; }

private:
    std::vector<Item_type> _stack;
    std::size_t _size;
};

#endif // ARRAY_STACK_H
