#ifndef COLLECTED_BAG_H
#define COLLECTED_BAG_H

#include <cstdlib>
#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <memory>
#include <sstream>
#include <iostream>

template<typename T>
class Bag_node;

template<typename T>
class Bag_iterator;

template<typename T>
class Bag;

template<typename T>
struct Bag_node_pointer_traits {
    using Node_type = Bag_node<T>;
    using Node_raw_pointer = Bag_node<T>*;
    using Node_owning_pointer = std::unique_ptr<Node_type>;
    using Value_type = T;
    using Shared_value_pointer = std::shared_ptr<Value_type>;
};

template<typename T>
class Bag_node {
public:
    using Node_traits = Bag_node_pointer_traits<T>;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Value_type = typename Node_traits::Value_type;
    using Shared_value_pointer = typename Node_traits::Shared_value_pointer;

    inline Bag_node() : _next{nullptr} {}

    inline Bag_node(T item) : _next{nullptr}, _item{item} {}

private:
    Value_type _item;
    Node_owning_pointer _next;

    template<typename>
    friend class Bag;

    template<typename>
    friend class Bag_iterator;
};

template<typename T>
class Bag_iterator {
    using Node_traits = Bag_node_pointer_traits<T>;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    Node_raw_pointer _ptr;

    template<typename>
    friend class Bag;

public:
    using iterator_category = std::forward_iterator_tag;
    using Value_type = typename Node_traits::Value_type;
    using Reference_type = Value_type&;

    inline Bag_iterator() noexcept : _ptr{nullptr} {}

    inline explicit Bag_iterator(Node_raw_pointer p) noexcept : _ptr{p} {}

    inline Reference_type operator*() const
    {
        return _ptr->_item;
    }

    inline Node_raw_pointer operator->() const
    {
        return _ptr;
    }

    inline Bag_iterator& operator++()
    {
        _ptr = _ptr->_next.get();
        return *this;
    }

    inline Bag_iterator operator++(int)
    {
        Bag_iterator t{*this};
        ++(*this);
        return t;
    }

    friend
    inline bool operator==(const Bag_iterator& x, const Bag_iterator& y)
    {
        return x._ptr == y._ptr;
    }

    friend
    inline bool operator!=(const Bag_iterator& x, const Bag_iterator& y) { return !(x == y); }
};

template<typename T>
class Bag {
public:
    using Node_traits = Bag_node_pointer_traits<T>;
    using Node_type = typename Node_traits::Node_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Value_type = typename Node_traits::Value_type;
    using Pointer_type = Value_type*;
    using Reference_type = Value_type&;
    using Shared_value_pointer = typename Node_traits::Shared_value_pointer;
    using Iterator_type = Bag_iterator<T>;
    using Const_iterator_type = Bag_iterator<T>;

    // inline Bag() = default;

    // ~Bag();

    inline bool is_empty() const noexcept { return _first == nullptr; }

    inline int size() const noexcept { return _n; }

    inline Iterator_type begin() const noexcept { return Iterator_type(_first.get()); }

    inline Iterator_type end() const noexcept { return Iterator_type(nullptr); }

    void add(Reference_type item)
    {
        auto old_first = std::move(_first);
        _first = std::unique_ptr<Node_type>{new Bag_node<Value_type>};
        _first->_item = item;
        _first->_next = std::move(old_first);
        ++_n;
    }

    std::string to_string() const
    {
        std::stringstream ss;
        ss << "Bag(\n";
        for (auto i : *this) {
            ss << "    Node(" << i << "),\n";
        }
        ss << ")\n";
        return ss.str();
    }

private:
    Node_owning_pointer _first;
    int _n;

    void _clear() noexcept
    {
        if (!is_empty()) {
            auto f = std::move(_first);
            _n = 0;
            while (f != nullptr) {
                auto np = f.release();
                f = std::move(f->_next);
                delete np;
            }
        }
    };
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Bag<T>& out)
{
    return os << out.to_string();
}

//template<typename T>
//Bag<T>::~Bag()
//{
//    clear();
//}

#endif //COLLECTED_BAG_H
