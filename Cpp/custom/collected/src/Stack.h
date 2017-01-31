#ifndef COLLECTED_STACK_H
#define COLLECTED_STACK_H

#include <iterator>
#include <sstream>

#include "utility.h"

template<typename T>
class Stack_node;

template<typename T>
class Stack_iterator;

template<typename T>
class Stack;

template<typename T>
class Stack_node {
public:
    using Node = Stack_node<T>;
    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;
    using Item = T;
private:
    Item _item;
    Owning_node_pointer _next;

    template<typename>
    friend class Stack_iterator;

    template<typename>
    friend class Stack;
};

template<typename T>
class Stack_iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using Node = Stack_node<T>;
    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;
    using Item = T;

    Stack_iterator() = default;

    Stack_iterator(const Stack_iterator&) = default;

    Stack_iterator(Stack_iterator&&) = default;

    ~Stack_iterator() = default;

    Stack_iterator& operator=(const Stack_iterator&) = default;

    Stack_iterator& operator=(Stack_iterator&&) = default;

    Stack_iterator(Raw_node_pointer first) : _current{first} {}

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

    Stack_iterator& operator++()
    {
        if (has_next()) {
            _current = _current->_next;
        }
        return *this;
    }

    Stack_iterator operator++(int)
    {
        Stack_iterator t{*this};
        ++(*this);
        return t;
    }

    friend
    inline bool operator==(const Stack_iterator& lhs, const Stack_iterator& rhs) { return lhs._current == rhs._current; }

    friend
    inline bool operator!=(const Stack_iterator& lhs, const Stack_iterator& rhs) { return !(lhs == rhs); }

private:
    Raw_node_pointer _current;
};

template<typename T>
class Stack {
public:
    using Node = Stack_node<T>;
    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;
    using Item = T;
    using Iterator_type = Stack_iterator<T>;

    Stack(const Stack&) = default;

    Stack(Stack&&) = default;

    Stack& operator=(const Stack&) = default;

    Stack& operator=(Stack&&) = default;

    Stack() : _first{nullptr}, _size{0} {}

    ~Stack()
    {
        Raw_node_pointer n{_first};
        while (n != nullptr) {
            Raw_node_pointer tmp{n->_next};
            delete n;
            n = tmp;
        }
    }

    inline bool is_empty() const noexcept { return _first == nullptr; }

    inline int size() const noexcept { return _size; }

    void push(Item& item)
    {
        Raw_node_pointer old_first{_first};
        _first = new Stack_node<Item>;
        _first->_item = item;
        _first->_next = old_first;
        ++_size;
    }

    Item pop()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Stack underflow"}; }
        Item item = _first->_item;
        Raw_node_pointer tmp{_first};
        _first = _first->_next;
        delete tmp;
        --_size;
        return item;
    }

    Item peek() const
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Stack underflow"}; }
        return _first->_item;
    }

    std::string to_string()
    {
        std::stringstream ss;
        ss << "Stack(\n";
        for (auto item : *this) {
            ss << "    " << item << "\n";
        }
        ss << ")";
        return ss.str();
    }

    inline Iterator_type begin() { return Stack_iterator<Item>{_first}; }

    inline Iterator_type end() { return Stack_iterator<Item>{nullptr}; }

private:
    Owning_node_pointer _first;
    int _size;
};

template<typename T>
inline std::ostream& operator<<(std::ostream& os, Stack<T>& out)
{
    return os << out.to_string();
}

#endif // COLLECTED_STACK_H
