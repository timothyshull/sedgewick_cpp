#ifndef COLLECTED_QUEUE_H
#define COLLECTED_QUEUE_H

#include <iterator>

#include "utility.h"

template<typename T>
class Queue_node;

template<typename T>
class Queue_iterator;

template<typename T>
class Queue;

template<typename T>
class Queue_node {
public:
    using Node = Queue_node<T>;
    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;
    using Item = T;
private:
    Item _item;
    Owning_node_pointer _next;

    template<typename>
    friend class Queue_iterator;

    template<typename>
    friend class Queue;
};

template<typename T>
class Queue_iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using Node = Queue_node<T>;
    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;
    using Item = T;

    Queue_iterator() = default;

    Queue_iterator(const Queue_iterator&) = default;

    Queue_iterator(Queue_iterator&&) = default;

    ~Queue_iterator() = default;

    Queue_iterator& operator=(const Queue_iterator&) = default;

    Queue_iterator& operator=(Queue_iterator&&) = default;

    Queue_iterator(Raw_node_pointer first) : _current{first} {}

    inline bool has_next() const noexcept { return _current != nullptr; }

    Item next()
    {
        if (!has_next()) { throw utility::No_such_element_exception{""}; }
        Item item{_current->_item};
        _current = _current->_next;
        return item;
    }

    inline Item operator*() const { return _current->_item; }

    inline Raw_node_pointer operator->() const { return _current; }

    Queue_iterator& operator++()
    {
        if (has_next()) {
            _current = _current->_next;
        }
        return *this;
    }

    Queue_iterator operator++(int)
    {
        Queue_iterator t{*this};
        ++(*this);
        return t;
    }

    friend
    inline bool operator==(const Queue_iterator& x, const Queue_iterator& y) { return x._current == y._current; }

    friend
    inline bool operator!=(const Queue_iterator& x, const Queue_iterator& y) { return !(x == y); }

private:
    Raw_node_pointer _current;
};

template<typename T>
class Queue {
public:
    using Node = Queue_node<T>;
    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;
    using Item = T;
    using Iterator_type = Queue_iterator<T>;

    Queue(const Queue&) = default;

    Queue(Queue&&) = default;

    Queue& operator=(const Queue&) = default;

    Queue& operator=(Queue&&) = default;

    Queue() : _first{nullptr}, _last{nullptr}, _size{0} {}

    ~Queue()
    {
        Raw_node_pointer n = _first;
        while (n != nullptr) {
            Raw_node_pointer tmp{n->_next};
            delete n;
            n = tmp;
        }
    }

    inline bool is_empty() const noexcept { return _first == nullptr; }

    inline int size() const noexcept { return _size; }

    Item peek() const
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Queue underflow"}; }
        return _first->_item;
    }

    void enqueue(Item& item)
    {
        Raw_node_pointer old_last = _last;
        _last = new Queue_node<Item>;
        _last->_item = item;
        _last->_next = nullptr;
        if (is_empty()) { _first = _last; }
        else { old_last->_next = _last; }
        ++_size;
    }

    Item dequeue()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Queue underflow"}; }
        Item item{_first->_item};
        Raw_node_pointer tmp{_first};
        _first = _first->_next;
        delete tmp;
        --_size;
        if (is_empty()) { _last = nullptr; }
        return item;
    }

    std::string to_string()
    {
        std::stringstream ss;
        ss << "Queue(\n";
        for (auto item : *this) {
            ss << "    " << item << "\n";
        }
        ss << ")";
        return ss.str();
    }

    inline Iterator_type begin() { return Queue_iterator<Item>{_first}; }

    inline Iterator_type end() { return Queue_iterator<Item>{nullptr}; }

private:
    Owning_node_pointer _first;
    Raw_node_pointer _last;
    int _size;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, Queue<T>& out)
{
    return os << out.to_string();
}

#endif // COLLECTED_QUEUE_H
