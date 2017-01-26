#ifndef BINOMIAL_MIN_PRIORITY_QUEUE_H
#define BINOMIAL_MIN_PRIORITY_QUEUE_H

#include <memory>
#include "utility.h"

template<typename Key>
class Binomial_min_pq_node;

template<typename Key>
class Binomial_min_pq_iterator;

template<typename Key>
class Binomial_min_pq_reverse_iterator;

template<typename T>
struct Binomial_min_pq_key_comparator;

template<typename Key, typename Comparator = Binomial_min_pq_key_comparator<Key>>
class Binomial_min_pq;

template<typename Key>
struct Binomial_min_pq_node_pointer_traits {
    using Key_type = Key;
    using Node_type = Binomial_min_pq_node<Key_type>;
    using Node_raw_pointer = Node_type*;
    using Node_owning_pointer = Node_type*;
    using Shared_key_pointer = std::shared_ptr<Key_type>;
    using Size_type = std::size_t;
};

template<typename Key>
class Binomial_min_pq_node {
public:
    using Node_traits = Binomial_min_pq_node_pointer_traits<Key>;
    using Key_type = typename Node_traits::Key_type;
    using Node_type = typename Node_traits::Node_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Shared_key_pointer = typename Node_traits::Shared_key_pointer;
    using Size_type = typename Node_traits::Size_type;

private:
    Shared_key_pointer _key;

    int _order;

    Node_owning_pointer _child;
    Node_owning_pointer _sibling;

    template<typename, typename, typename>
    friend class Binomial_min_pq;

    template<typename, typename>
    friend class Binomial_min_pq_iterator;

    template<typename, typename>
    friend class Binomial_min_pq_reverse_iterator;
};

template<typename Key, typename Value>
class Binomial_min_pq_iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using Node_traits = Binomial_min_pq_node_pointer_traits<Key>;
    using Key_type = typename Node_traits::Key_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;

    Binomial_min_pq_iterator() noexcept = delete;

    Binomial_min_pq_iterator(const Binomial_min_pq_iterator&) = default;

    Binomial_min_pq_iterator(Binomial_min_pq_iterator&&) = default;

    ~Binomial_min_pq_iterator() = default;

    Binomial_min_pq_iterator& operator=(const Binomial_min_pq_iterator&) = default;

    Binomial_min_pq_iterator& operator=(Binomial_min_pq_iterator&&) = default;

    explicit Binomial_min_pq_iterator(Binomial_min_pq<Key_type>& pq) noexcept : _data{}, _current{pq._head}
    {
        _clone(pq._head, false, false, nullptr);
    }

    Binomial_min_pq_iterator(Binomial_min_pq<Key_type>& pq, Node_raw_pointer current) noexcept : _data{}, _current{current}
    {
        _clone(pq._head, false, false, nullptr);
    }

    inline Node_raw_pointer operator*() const
    {
        return _current;
    }

    inline Node_raw_pointer operator->() const
    {
        return _current;
    }

    inline Binomial_min_pq_iterator& operator++()
    {
        _data.delete_min();
        _current = _data._head;
        return *this;
    }

    inline Binomial_min_pq_iterator operator++(int)
    {
        Binomial_min_pq_iterator t{*this};
        ++(*this);
        return t;
    }

    friend
    inline bool operator==(const Binomial_min_pq_iterator& x, const Binomial_min_pq_iterator& y)
    {
        return x._data._head == y._data._head && x._current == y._current;
    }

    friend
    inline bool operator!=(const Binomial_min_pq_iterator& x, const Binomial_min_pq_iterator& y) { return !(x == y); }

private:
    Binomial_min_pq<Key_type> _data;
    Node_raw_pointer _current;

    Node_raw_pointer _clone(Node_raw_pointer x, bool is_parent, bool is_child, Node_raw_pointer parent)
    {
        if (x == nullptr) { return nullptr; }
        Node_raw_pointer node{new Binomial_min_pq_node<Key_type>};
        node->_key = x->_key;
        node->_sibling = _clone(x->_sibling, false, false, parent);
        node->_child = _clone(x->_child, false, true, node);
        return node;
    }

    template<typename>
    friend class Binomial_min_pq;
};

template<typename T>
struct Binomial_min_pq_key_comparator {
    int operator()(const T& x, const T& y) const
    {
        if (x < y) {
            return -1;
        } else if (y < x) {
            return 1;
        }
        return 0;
    }
};

template<typename Key, typename Comparator = Binomial_min_pq_key_comparator<Key>>
class Binomial_min_pq {
public:
    using Node_traits = Binomial_min_pq_node_pointer_traits<Key>;
    using Node_type = typename Node_traits::Node_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Shared_key_pointer = typename Node_traits::Shared_key_pointer;
    using Key_type = typename Node_traits::Key_type;
    using Comparator_type = Comparator;

    using Size_type = std::size_t;
    using Difference_type = std::ptrdiff_t;
    using Iterator_type = Binomial_min_pq_iterator<Key_type>;

    Binomial_min_pq() : _comp{} {}

    Binomial_min_pq(std::vector<Key_type>& a) : _comp{}
    {
        for (auto k : a) { insert(k); }
    }

    bool is_empty()
    {
        return _head == nullptr;
    }

    int size()
    {
        int result{0};
        int tmp;
        for (Node_raw_pointer node = _head; node != nullptr; node = node->_sibling) {
            if (node->_order > 30) {
                throw utility::Arithmetic_exception{"The number of elements cannot be evaluated, but the priority _queue is still valid."};
            }
            tmp = 1 << node->_order;
            result |= tmp;
        }
        return result;
    }

    void insert(Key_type& key)
    {
        Node_raw_pointer x{new Binomial_min_pq_node<Key_type>{}};
        x->_key = key;
        x->_order = 0;
        Binomial_min_pq<Key> h;
        h._head = x;
        this->_head = this->create_union(h)._head;
    }

    Key min_key()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Priority _queue is empty"}; }
        Node_raw_pointer min = _head;
        Node_raw_pointer current = _head;
        while (current->_sibling != nullptr) {
            min = (_greater(min->_key, current->_sibling->_key)) ? current : min;
            current = current->_sibling;
        }
        return min->_key;
    }

    Key delete_min()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Priority _queue is empty"}; }
        Node_raw_pointer min = _erase_min();
        Node_raw_pointer x = (min->_child == nullptr) ? min : min->_child;
        if (min->_child != nullptr) {
            min->_child = nullptr;
            Node_raw_pointer prevx = nullptr;
            Node_raw_pointer nextx = x->_sibling;
            while (nextx != nullptr) {
                x->_sibling = prevx;
                prevx = x;
                x = nextx;
                nextx = nextx->_sibling;
            }
            x->_sibling = prevx;
            Binomial_min_pq<Key> h;
            h._head = x;
            _head = create_union(h)._head;
        }
        return min->_key;
    }

    Binomial_min_pq<Key>& create_union(Binomial_min_pq<Key>& heap)
    {
        _head = _merge(new Binomial_min_pq_node<Key_type>, this->_head, heap._head)->_sibling;
        Node_raw_pointer x{_head};
        Node_raw_pointer prev_x{nullptr};
        Node_raw_pointer next_x{x->_sibling};
        while (next_x != nullptr) {
            if (x->_order < next_x->_order ||
                (next_x->_sibling != nullptr && next_x->_sibling->_order == x->_order)) {
                prev_x = x;
                x = next_x;
            } else if (_greater(next_x->_key, x->_key)) {
                x->_sibling = next_x->_sibling;
                _link(next_x, x);
            } else {
                if (prev_x == nullptr) {
                    this->_head = next_x;
                } else {
                    prev_x->_sibling = next_x;
                }
                _link(x, next_x);
                x = next_x;
            }
            next_x = x->_sibling;
        }
        return *this;
    }

    Iterator_type begin() { return Iterator_type{*this}; }

    Iterator_type end() { return Iterator_type(nullptr); }

private:
    Node_owning_pointer _head;
    Comparator_type _comp;

    template<typename, typename>
    friend class Binomial_min_pq_iterator;

    bool _greater(Key_type& n, Key_type& m)
    {
        return _comp(m, n);
    }

    void _link(Node_raw_pointer root1, Node_raw_pointer root2)
    {
        root1->_sibling = root2->_child;
        root2->_child = root1;
        root2->_order++;
    }

    Node_raw_pointer _erase_min()
    {
        Node_raw_pointer min{_head};
        Node_raw_pointer previous{nullptr};
        Node_raw_pointer current{_head};
        while (current->_sibling != nullptr) {
            if (_greater(min->_key, current->_sibling->_key)) {
                previous = current;
                min = current->_sibling;
            }
            current = current->_sibling;
        }
        previous->_sibling = min->_sibling;
        if (min == _head) { _head = min->_sibling; }
        return min;
    }

    Node_raw_pointer _merge(Node_raw_pointer h, Node_raw_pointer x, Node_raw_pointer y)
    {
        if (x == nullptr && y == nullptr) { return h; }
        else if (x == nullptr) { h->_sibling = _merge(y, nullptr, y->_sibling); }
        else if (y == nullptr) { h->_sibling = _merge(x, x->_sibling, nullptr); }
        else if (x->_order < y->_order) { h->_sibling = _merge(x, x->_sibling, y); }
        else { h->_sibling = _merge(y, x, y->_sibling); }
        return h;
    }

};

#endif // BINOMIAL_MIN_PRIORITY_QUEUE_H
