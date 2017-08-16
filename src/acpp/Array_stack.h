// Program 4.7 - Array implementation of a pushdown stack
#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <cstddef>
#include <vector>

template<typename Item_t>
class Array_stack {
public:
    Array_stack() = default;

    ~Array_stack() = default;

    Array_stack(const Array_stack&) = default;

    Array_stack(Array_stack&&) = default;

    Array_stack& operator=(const Array_stack&) = default;

    explicit Array_stack(std::size_t max_elements) : _stack(max_elements) {}

    inline bool empty() const noexcept { return _stack.empty(); }

    inline void push(Item_t& item) { _stack.push_back(item); }

    inline void push(Item_t&& item) { _stack.push_back(item); }

    inline Item_t pop() { return _stack.pop_back(); }

private:
    std::vector<Item_t> _stack;
};

#endif // ARRAY_STACK_H
