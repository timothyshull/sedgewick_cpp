#ifndef STACK_H
#define STACK_H

#include <memory>
#include <sstream>

#include "src/utility.h"

template<typename T>
class Stack_node;

template<typename T>
class Stack_iterator;

template<typename T>
class Stack;

template<typename T>
struct Stack_node_pointer_traits {
    using Node_type = Stack_node<T>;
    using Node_raw_pointer = Stack_node<T>*;
    using Node_owning_pointer = std::unique_ptr<Node_type>;
    using Value_type = T;
    using Shared_value_pointer = std::shared_ptr<Value_type>;
};

template<typename T>
class Stack_node {
public:
    using Node_traits = Stack_node_pointer_traits<T>;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Value_type = typename Node_traits::Value_type;
    using Shared_value_pointer = typename Node_traits::Shared_value_pointer;

private:
    Value_type _item;
    Node_owning_pointer _next;

    template<typename>
    friend class Stack;

    template<typename>
    friend class Stack_iterator;
};

template<typename T>
class Stack_iterator {
public:
    using Node_traits = Stack_node_pointer_traits<T>;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;

private:
    Node_raw_pointer _ptr;

    template<typename>
    friend class Stack;

public:
    using iterator_category = std::forward_iterator_tag;
    using Value_type = typename Node_traits::Value_type;
    using Reference_type = Value_type&;

    inline Stack_iterator() noexcept : _ptr{nullptr} {}

    inline explicit Stack_iterator(Node_raw_pointer p) noexcept : _ptr{p} {}

    inline Reference_type operator*() const
    {
        return _ptr->_item;
    }

    inline Node_raw_pointer operator->() const
    {
        return _ptr;
    }

    inline Stack_iterator& operator++()
    {
        _ptr = _ptr->_next.get();
        return *this;
    }

    inline Stack_iterator operator++(int)
    {
        Stack_iterator t{*this};
        ++(*this);
        return t;
    }

    friend
    inline bool operator==(const Stack_iterator& x, const Stack_iterator& y)
    {
        return x._ptr == y._ptr;
    }

    friend
    inline bool operator!=(const Stack_iterator& x, const Stack_iterator& y) { return !(x == y); }
};

template<typename T>
class Stack {
public:
    using Node_traits = Stack_node_pointer_traits<T>;
    using Node_type = typename Node_traits::Node_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Value_type = typename Node_traits::Value_type;
    using Pointer_type = Value_type*;
    using Reference_type = Value_type&;
    using Shared_value_pointer = typename Node_traits::Shared_value_pointer;
    using Iterator_type = Stack_iterator<T>;
    using Const_iterator_type = Stack_iterator<T>;

    Stack() = default;

    Stack(const Stack& s) : _n{s._n}
    {
        if (!s.is_empty()) {
            _first = std::unique_ptr<Node_type>{};
            Node_raw_pointer n1{s._first.get()};
            Node_raw_pointer n2{_first.get()};

            while (n1 != nullptr) {
                n2->_item = n1->_item;
                if (n1->_next != nullptr) {
                    n2->_next = std::unique_ptr<Node_type>{};
                } else {
                    n2->_next = nullptr;
                }
                n1 = n1->_next.get();
                n2 = n2->_next.get();
            }
        }
    }

    Stack(Stack&& s) : _first{std::move(s._first)}, _n{s._n} {}

    ~Stack()
    {
        _clear();
    }

    Stack& operator=(const Stack& rhs)
    {
        _n = rhs._n;
        if (!rhs.is_empty()) {
            _first = std::unique_ptr<Node_type>{};
            Node_raw_pointer n1{rhs._first.get()};
            Node_raw_pointer n2{_first.get()};

            while (n1 != nullptr) {
                n2->_item = n1->_item;
                if (n1->_next != nullptr) {
                    n2->_next = std::unique_ptr<Node_type>{};
                } else {
                    n2->_next = nullptr;
                }
                n1 = n1->_next.get();
                n2 = n2->_next.get();
            }
        }
        return *this;
    };

    Stack& operator=(Stack&& rhs)
    {
        _first = std::move(rhs._first);
        _n = rhs._n;
        return *this;
    }

    inline bool is_empty() const { return _first == nullptr; }

    inline int size() const { return _n; }

    void push(Reference_type item)
    {
        auto old_first = std::move(_first);
        _first = std::unique_ptr<Node_type>{new Stack_node<Value_type>};
        _first->_item = item;
        _first->_next = std::move(old_first);
        ++_n;
    }

    Value_type pop()
    {
        if (is_empty()) {
            throw utility::No_such_element_exception("Stack underflow");
        }
        Value_type item = _first->_item;
        _first = std::move(_first->_next);
        --_n;
        return item;
    }

    Value_type peek() const
    {
        if (is_empty()) {
            throw utility::No_such_element_exception("Stack underflow");
        }
        return _first->_item;
    }

    std::string to_string() const
    {
        std::stringstream ss;
        ss << "Stack(\n";
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
    int _n;

    void _clear() noexcept
    {
        _clear(_first);
    }

    void _clear(Node_owning_pointer& node) noexcept
    {
        if (node != nullptr) {
            _clear(node->_next);
            node.reset(nullptr);
        }
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& out)
{
    return os << out.to_string();
}

#endif // STACK_H
