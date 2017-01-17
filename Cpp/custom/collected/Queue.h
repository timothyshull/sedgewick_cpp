#ifndef QUEUE_H
#define QUEUE_H

#include <memory>
#include <sstream>

#include "utility.h"

template<typename T>
class Queue_node;

template<typename T>
class Queue_iterator;

template<typename T>
class Queue;

template<typename T>
struct Queue_node_pointer_traits {
    using Node_type = Queue_node<T>;
    using Node_raw_pointer = Queue_node<T>*;
    using Node_owning_pointer = std::unique_ptr<Node_type>;
    using Value_type = T;
    using Shared_value_pointer = std::shared_ptr<Value_type>;
};

template<typename T>
class Queue_node {
public:
    using Node_traits = Queue_node_pointer_traits<T>;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Value_type = typename Node_traits::Value_type;
    using Shared_value_pointer = typename Node_traits::Shared_value_pointer;

private:
    Value_type _item;
    Node_owning_pointer _next;

    template<typename>
    friend class Queue;

    template<typename>
    friend class Queue_iterator;
};

template<typename T>
class Queue_iterator {
public:
    using Node_traits = Queue_node_pointer_traits<T>;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;

private:
    Node_raw_pointer _ptr;

    template<typename>
    friend class Queue;

public:
    using iterator_category = std::forward_iterator_tag;
    using Value_type = typename Node_traits::Value_type;
    using Reference_type = Value_type&;

    inline Queue_iterator() noexcept : _ptr{nullptr} {}

    inline explicit Queue_iterator(Node_raw_pointer p) noexcept : _ptr{p} {}

    inline Reference_type operator*() const
    {
        return _ptr->_item;
    }

    inline Node_raw_pointer operator->() const
    {
        return _ptr;
    }

    inline Queue_iterator& operator++()
    {
        _ptr = _ptr->_next.get();
        return *this;
    }

    inline Queue_iterator operator++(int)
    {
        Queue_iterator t{*this};
        ++(*this);
        return t;
    }

    friend
    inline bool operator==(const Queue_iterator& x, const Queue_iterator& y)
    {
        return x._ptr == y._ptr;
    }

    friend
    inline bool operator!=(const Queue_iterator& x, const Queue_iterator& y) { return !(x == y); }
};

template<typename T>
class Queue {
public:
    using Node_traits = Queue_node_pointer_traits<T>;
    using Node_type = typename Node_traits::Node_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Value_type = typename Node_traits::Value_type;
    using Pointer_type = Value_type*;
    using Reference_type = Value_type&;
    using Shared_value_pointer = typename Node_traits::Shared_value_pointer;
    using Iterator_type = Queue_iterator<T>;
    using Const_iterator_type = Queue_iterator<T>;

    Queue() : _first{nullptr}, _n{0} {}

    inline bool is_empty() const { return _first == nullptr; }

    inline int size() const { return _n; }

    void enqueue(Value_type item)
    {
        if (is_empty()) {
            _first = std::unique_ptr<Node_type>{new Queue_node<Value_type>};
            _last = _first.get();
        } else {
            auto old_last = _last;
            old_last->_next = std::unique_ptr<Node_type>{new Queue_node<Value_type>};
            _last = old_last->_next.get();
        }
        _last->_item = item;
        _last->_next = nullptr;
        ++_n;
    }

    Value_type dequeue()
    {
        if (is_empty()) {
            throw utility::No_such_element_exception("Queue underflow");
        }
        Value_type item = _first->_item;
        _first = std::move(_first->_next);
        --_n;
        if (is_empty()) {
            _first = nullptr;
            _last = nullptr;
        }
        return item;
    }

    Value_type peek() const
    {
        if (is_empty()) {
            throw utility::No_such_element_exception("Queue underflow");
        }
        return _first->_item;
    }

    std::string to_string() const
    {
        std::stringstream ss;
        ss << "Queue(\n";
        for (auto i : *this) {
            ss << "    Node(" << i << "),\n";
        }
        ss << ")\n";
        return ss.str();
    }

    inline Iterator_type begin() const noexcept
    {
        return Iterator_type(_first.get());
    }

    inline Iterator_type end() const noexcept
    {
        return Iterator_type(nullptr);
    }

private:
    Node_owning_pointer _first;
    Node_raw_pointer _last;
    int _n;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& out)
{
    return os << out.to_string();
}

#endif //QUEUE_H
