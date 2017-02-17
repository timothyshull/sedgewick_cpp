#ifndef BAG_H
#define BAG_H

#include <iterator>

#include "utility.h"

template<typename T>
class Bag;

template<typename T>
class Bag_node;

template<typename T>
class Bag_iterator;

template<typename T>
class Bag_node {
public:
    using Node = Bag_node<T>;
    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;
    using Item = T;
private:
    Item _item;
    Owning_node_pointer _next;

    template<typename>
    friend class Bag;

    template<typename>
    friend class Bag_iterator;
};

template<typename T>
class Bag_iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using Node = Bag_node<T>;
    using Raw_node_pointer = Node*;
    using Item = T;

    Bag_iterator() = default;

    Bag_iterator(const Bag_iterator&) = default;

    Bag_iterator(Bag_iterator&&) = default;

    ~Bag_iterator() = default;

    Bag_iterator& operator=(const Bag_iterator&) = default;

    Bag_iterator& operator=(Bag_iterator&&) = default;

    Bag_iterator(Raw_node_pointer first) : _current{first} {}

    inline bool has_next() const noexcept { return _current != nullptr; }

    Item next()
    {
        if (!has_next()) { throw utility::No_such_element_exception{""}; }
        Item item = _current->_item;
        _current = _current->_next;
        return item;
    }

    inline Item operator*() const { return _current->_item; }

    inline Raw_node_pointer operator->() const { return _current; }

    Bag_iterator& operator++()
    {
        if (has_next()) {
            _current = _current->_next;
        }
        return *this;
    }

    Bag_iterator operator++(int)
    {
        Bag_iterator t{*this};
        ++(*this);
        return t;
    }

    friend
    inline bool operator==(const Bag_iterator& x, const Bag_iterator& y) { return x._current == y._current; }

    friend
    inline bool operator!=(const Bag_iterator& x, const Bag_iterator& y) { return !(x == y); }

private:
    Raw_node_pointer _current;
};

template<typename T>
class Bag {
public:
    using Node = Bag_node<T>;
    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;
    using Item = T;
    using Iterator_type = Bag_iterator<T>;

    Bag(const Bag&) = default;

    Bag(Bag&&) = default;

    Bag& operator=(const Bag&) = default;

    Bag& operator=(Bag&&) = default;

    Bag() : _first{nullptr}, _size{0} {}

    ~Bag()
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

    void add(Item& item)
    {
        Raw_node_pointer old_first = _first;
        _first = new Bag_node<Item>;
        _first->_item = item;
        _first->_next = old_first;
        ++_size;
    }

    std::string to_string() const
    {
        std::stringstream ss;
        ss << "Bag(\n";
        for (auto item : *this) {
            ss << "    " << item << "\n";
        }
        ss << ")";
        return ss.str();
    }

    inline Iterator_type begin() { return Bag_iterator<Item>{_first}; }

    inline Iterator_type end() { return Bag_iterator<Item>{nullptr}; }

private:
    Owning_node_pointer _first;
    int _size;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Bag<T>& out)
{
    return os << out.to_string();
}

#endif // BAG_H
