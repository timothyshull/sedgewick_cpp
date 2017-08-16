// Program 4.15 - FIFO queue array implementation
#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include <cstddef>
#include <deque>

template<typename Item_t>
class Array_queue {
public:
    Array_queue() = default;

    ~Array_queue() = default;

    Array_queue(const Array_queue&) = default;

    Array_queue(Array_queue&&) = default;

    Array_queue& operator=(const Array_queue&) = default;

    explicit Array_queue(std::size_t max_elements) : _queue(max_elements + 1) {}

    inline bool empty() const noexcept { return _queue.empty(); }

    void push(Item_t& item) { _queue.push_back(item); }

    void push(Item_t&& item) { _queue.push_back(item); }

    Item_t pop() { return _queue.pop_front(); }

private:
    std::deque<Item_t> _queue;
};

#endif // ARRAY_QUEUE_H
