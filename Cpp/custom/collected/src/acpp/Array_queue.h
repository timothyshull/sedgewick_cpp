// Program 4.15 - FIFO queue array implementation
#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include <cstddef>
#include <deque>

template<typename Item_type>
class Array_queue {
public:
    Array_queue() = default;

    ~Array_queue() = default;

    Array_queue(const Array_queue&) = default;

    Array_queue(Array_queue&&) = default;

    Array_queue& operator=(const Array_queue&) = default;

    explicit Array_queue(std::size_t max_elements) : _queue(max_elements + 1) {}

    inline bool empty() const noexcept { return _queue.empty(); }

    void push(Item_type& item) { _queue.push_back(item); }

    void push(Item_type&& item) { _queue.push_back(item); }

    Item_type pop() { return _queue.pop_front(); }

private:
    std::deque<Item_type> _queue;
};

#endif // ARRAY_QUEUE_H
