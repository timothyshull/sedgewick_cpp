// Program 4.16 - Stack with index items and no duplicates
#ifndef STACK_SET_H
#define STACK_SET_H

#include <cstddef>
#include <vector>
#include <deque>

template<typename Item_type> // Item_type must be an integer type
class Stack_set {
public:
    Stack_set(std::size_t size)
            : _stack(size),
              _size{0},
              _on_stack(size, false) {}

    inline bool empty() const noexcept { return _size == 0; }

    void push(Item_type& item)
    {
        if (_on_stack[item]) { return; }
        _stack[_size++] = item;
        _on_stack[item] = true;
    }

    void push(Item_type&& item)
    {
        if (_on_stack[item]) { return; }
        _stack[_size++] = item;
        _on_stack[item] = true;
    }

    Item_type pop()
    {
        _on_stack[_stack[--_size]] = false;
        return _stack[_size];
    }

private:
    std::vector<Item_type> _stack;
    std::deque<bool> _on_stack; // used to test whether the item is already on the stack
    std::size_t _size;
};

#endif // STACK_SET_H
