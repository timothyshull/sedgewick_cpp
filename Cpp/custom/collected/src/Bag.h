#ifndef BAG_H
#define BAG_H

#include <iterator>
#include <forward_list>

#include "utility.h"

template<typename Item_type>
class Bag;

template<typename Item_type>
class Bag_node;

template<typename Item_type>
class Bag_iterator;

template<typename Item_type>
class Bag_node {
public:
    using Node = Bag_node<Item_type>;
    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;
    using Item = Item_type;

private:
    Item _item;
    Owning_node_pointer _next;

public:
    Bag_node() : _next{nullptr} {}

    ~Bag_node() { if (_next != nullptr) { delete _next; }}

    explicit Bag_node(Item_type item) : _item{item}, _next{nullptr} {}

    Bag_node(Item item, Raw_node_pointer next) : _item{item}, _next{next} {}

    Bag_node(const Bag_node&) = delete;

    Bag_node(Bag_node&& rhs) : _item{rhs._item}, _next{rhs._next} { rhs._next = nullptr; }

    Bag_node& operator=(const Bag_node&) = delete;

    Bag_node& operator=(Bag_node&& rhs)
    {
        if (&rhs == this) { return *this; }
        _item = rhs._item;
        _next = rhs._next;
        rhs._next = nullptr;
        return *this;
    }

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
    using Item_type = T;

private:
    Raw_node_pointer _current;

public:
    Bag_iterator(Raw_node_pointer first) : _current{first} {}

    Bag_iterator() : _current{nullptr} {}

    Bag_iterator(const Bag_iterator&) = default;

    Bag_iterator(Bag_iterator&&) = default;

    ~Bag_iterator() = default;

    Bag_iterator& operator=(const Bag_iterator&) = default;

    Bag_iterator& operator=(Bag_iterator&&) = default;

    inline bool has_next() const noexcept { return _current->_next != nullptr; }

    Item_type next()
    {
        if (!has_next()) { throw utility::No_such_element_exception{"next() called on Bag_iterator at end"}; }
        auto item = _current->_item;
        _current = _current->_next;
        return item;
    }

    inline Item_type& operator*() const { return _current->_item; }

    inline Item_type* operator->() const { return std::addressof(_current->_item); }

    Bag_iterator& operator++()
    {
        if (has_next()) { _current = _current->_next; }
        else { _current = nullptr; }
        return *this;
    }

    Bag_iterator operator++(int)
    {
        auto t = *this;
        ++(*this);
        return t;
    }

    friend
    inline bool operator==(const Bag_iterator& lhs, const Bag_iterator& rhs) { return lhs._current == rhs._current; }

    friend
    inline bool operator!=(const Bag_iterator& lhs, const Bag_iterator& rhs) { return !(rhs == lhs); }

};

template<typename T>
class Bag {
public:
    using Node = Bag_node<T>;
    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;
    using Item_type = T;
    using Iterator_type = Bag_iterator<T>;

private:
    Owning_node_pointer _first;
    int _size;

public:
    Bag(const Bag&) = default;

    Bag(Bag&&) = default;

    Bag& operator=(const Bag&) = default;

    Bag& operator=(Bag&&) = default;

    Bag() : _first{nullptr}, _size{0} {}

    ~Bag() { if (_first != nullptr) { delete _first; }}

    inline bool is_empty() const noexcept { return _first == nullptr; }

    inline int size() const noexcept { return _size; }

    void add(const Item_type& item)
    {
        auto old_first = _first;
        _first = new Bag_node<Item_type>;
        _first->_item = item;
        _first->_next = old_first;
        ++_size;
    }

    void add(Item_type&& item)
    {
        auto old_first = _first;
        _first = new Bag_node<Item_type>;
        _first->_item = item;
        _first->_next = old_first;
        ++_size;
    }

    std::string to_string() const
    {
        std::stringstream ss;
        ss << "Bag(\n";
        for (auto& item : *this) {
            ss << "    " << item << ",\n";
        }
        ss << ")";
        return ss.str();
    }

    inline Iterator_type begin() const { return Bag_iterator<Item_type>{_first}; }

    inline Iterator_type end() const { return Bag_iterator<Item_type>{nullptr}; }

    inline const Iterator_type cbegin() const { return Bag_iterator<Item_type>{_first}; }

    inline const Iterator_type cend() const { return Bag_iterator<Item_type>{nullptr}; }
};

template<typename Item_type>
inline std::ostream& operator<<(std::ostream& os, const Bag<Item_type>& out) { return os << out.to_string(); }

#endif // BAG_H
