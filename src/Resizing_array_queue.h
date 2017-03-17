#ifndef RESIZING_ARRAY_QUEUE_H
#define RESIZING_ARRAY_QUEUE_H

#include <vector>
#include "utility.h"

// TODO: wraparound iterator wrapper
template<typename T>
class Resizing_array_queue {
public:
    using Iterator_type = typename std::vector<T>::iterator;

    Resizing_array_queue()
            : _queue(static_cast<std::vector<T>::size_type>(2)),
              _size{2},
              _first{0},
              _last{0} {}

    inline bool is_empty() const noexcept { return _size == 0; }

    inline int size() const noexcept { return _size; }

    void enqueue(T& item)
    {
        if (_size == _queue.size()) { resize(2 * _queue.size()); }
        _queue[_last++] = item;
        if (_last == _queue.size()) { _last = 0; }
        ++_size;
    }

    void enqueue(T&& item)
    {
        if (_size == _queue.size()) { resize(2 * _queue.size()); }
        _queue[_last++] = item;
        if (_last == _queue.size()) { _last = 0; }
        ++_size;
    }

    T dequeue()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Queue underflow"}; }
        T item = _queue[_first];
        _queue[_first] = 0; // zero it out
        --_size;
        ++_first;
        if (_first == _queue.size()) { _first = 0; }
        if (_size > 0 && _size == _queue.size() / 4) { resize(_queue.size() / 2); }
        return item;
    }

    T peek()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Queue underflow"}; }
        return _queue[_first];
    }

    inline Iterator_type begin() { return _queue.begin() + _first; }

    inline Iterator_type end() { return _queue.end() + _last; }

private:
    std::vector<T> _queue;
    int _size;
    int _first;
    int _last;

    void resize(std::size_t capacity)
    {
        utility::alg_assert(capacity >= _size, "Resizing_array_queue resize called with capacity less than current size");
        utility::alg_assert(capacity < _queue.max_size(), "Resizing_array_queue resize called with capacity greater than or equal to the max size");
        std::vector<T> temp(capacity);
        for (int i{0}; i < _size; ++i) {
            temp[i] = _queue[(_first + i) % _queue.size()];
        }
        _queue = temp;
        _first = 0;
        _last = _size;
    }
};

#endif // RESIZING_ARRAY_QUEUE_H
