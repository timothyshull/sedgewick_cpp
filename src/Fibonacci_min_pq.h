#ifndef FIBONACCI_MIN_PQ_H
#define FIBONACCI_MIN_PQ_H

#include <memory>
#include <vector>
#include <map>
#include "utility.h"

template<typename Key>
class Fibonacci_min_pq_node;

template<typename T>
struct Fibonacci_min_pq_key_comparator;

template<typename Key, typename Comparator = Fibonacci_min_pq_key_comparator<Key>>
class Fibonacci_min_pq_iterator;

template<typename Key, typename Comparator = Fibonacci_min_pq_key_comparator<Key>>
class Fibonacci_min_pq;

template<typename Key>
struct Fibonacci_min_pq_node_pointer_traits {
    using Key_type = Key;

    using Node_type = Fibonacci_min_pq_node<Key_type>;
    using Node_raw_pointer = Node_type*;
    using Node_owning_pointer = Node_type*;
    using Size_type = std::size_t;
};

template<typename Key>
class Fibonacci_min_pq_node {
public:
    using Node_traits = Fibonacci_min_pq_node_pointer_traits<Key>;
    using Key_type = typename Node_traits::Key_type;
    using Node_type = typename Node_traits::Node_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;

private:
    Key_type _key;

    int _order;

    Node_owning_pointer _prev;
    Node_owning_pointer _next;
    Node_owning_pointer _child;

    template<typename, typename, typename>
    friend class Fibonacci_min_pq;

    template<typename, typename>
    friend class Fibonacci_min_pq_iterator;

    template<typename, typename>
    friend class Fibonacci_min_pq_reverse_iterator;
};

template<typename Key, typename Comparator>
class Fibonacci_min_pq_iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using Node_traits = Fibonacci_min_pq_node_pointer_traits<Key>;
    using Key_type = typename Node_traits::Key_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Comparator_type = Comparator;

    Fibonacci_min_pq_iterator() : _copy{}, _original{nullptr} {};

    explicit Fibonacci_min_pq_iterator(Fibonacci_min_pq<Key_type, Comparator_type>& pq) noexcept : _copy{0}, _original{&pq}
    {
        _insert_all(_original->_head);
    }

    inline Node_raw_pointer operator*() const
    {
        return _copy._head;
    }

    inline Node_raw_pointer operator->() const
    {
        return _copy._head;
    }

    inline Fibonacci_min_pq_iterator& operator++()
    {
        if (!_has_next()) {
            throw utility::No_such_element_exception{"Incrementing an empty Fibonacci_min_pq_iterator"};
        }
        _copy.delete_min();
        return *this;
    }

    inline Fibonacci_min_pq_iterator operator++(int)
    {
        Fibonacci_min_pq_iterator t{*this};
        ++(*this);
        return t;
    }

    friend
    inline bool operator==(const Fibonacci_min_pq_iterator& x, const Fibonacci_min_pq_iterator& y)
    {
        return x._original == y._original && x._copy._head == y._copy._head;
    }

    friend
    inline bool operator!=(const Fibonacci_min_pq_iterator& x, const Fibonacci_min_pq_iterator& y) { return !(x == y); }

private:
    Fibonacci_min_pq<Key_type> _copy;
    Fibonacci_min_pq<Key_type>* _original;

    void _insert_all(Node_raw_pointer head) {
        if (head == nullptr) return;
        Node_raw_pointer x{head};
        do {
            _copy.insert(x->_key);
            _insert_all(x->_child);
            x = x->_next;
        } while (x != head);
    }

    inline bool _has_next() const { return !_copy.is_empty(); }

    template<typename>
    friend class Fibonacci_min_pq;
};

template<typename T>
struct Fibonacci_min_pq_key_comparator {
    bool operator()(const T& x, const T& y) const
    {
        return x < y;
    }
};

template<typename Key, typename Comparator>
class Fibonacci_min_pq {
public:
    using Node_traits = Fibonacci_min_pq_node_pointer_traits<Key>;
    using Node_type = typename Node_traits::Node_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Key_type = typename Node_traits::Key_type;
    using Comparator_type = Comparator;

    using Iterator_type = Fibonacci_min_pq_iterator<Key_type>;

    Iterator_type begin() { return Iterator_type{*this}; }

    Iterator_type end() { return Iterator_type{}; }

    Fibonacci_min_pq() : _comp{} {}

    Fibonacci_min_pq(std::vector<Key_type>& a) : _comp{}
    {
        for (auto k : a) { insert(k); }
    }

    inline bool is_empty() const { return _size == 0; }

    inline int size() const { return _size; }

    void insert(Key key)
    {
        Node_raw_pointer x{new Fibonacci_min_pq_node<Key_type>};
        x->_key = key;
        ++_size;
        _head = insert(x, _head);
        if (_min == nullptr) { _min = _head; }
        else { _min = (greater(_min->_key, key)) ? _head : _min; }
    }

    Key min_key()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Priority _queue is empty"}; }
        return _min->_key;
    }

    Key delete_min()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Priority _queue is empty"}; }
        _head = cut(_min, _head);
        Node_raw_pointer x = _min->_child;
        Key key = _min->_key;
        _min->_key = nullptr;
        if (x != nullptr) {
            _head = meld(_head, x);
            _min->_child = nullptr;
        }
        _size--;
        if (!is_empty()) { consolidate(); }
        else { _min = nullptr; }
        return key;
    }

    Fibonacci_min_pq<Key_type, Comparator_type>& create_union(Fibonacci_min_pq<Key_type, Comparator_type>& rhs)
    {
        _head = meld(_head, rhs._head);
        _min = (greater(_min->_key, rhs._min->_key)) ? rhs._min : _min;
        _size = rhs._size + rhs._size;
        return *this;
    }

private:
    Node_owning_pointer _head;
    Node_raw_pointer _min;
    int _size;
    std::map<int, Node_raw_pointer> _table;
    Comparator_type _comp;

    template<typename, typename>
    friend class Fibonacci_min_pq_iterator;

    template<typename, typename>
    friend class Fibonacci_min_pq_reverse_iterator;

    bool greater(Key n, Key m)
    {
        if (n == nullptr) { return false; }
        if (m == nullptr) { return true; }
        return _comp.compare(n, m) > 0;
    }

    void link(Node_raw_pointer root1, Node_raw_pointer root2)
    {
        root2->_child = insert(root1, root2->_child);
        root2->_order++;
    }

    void consolidate()
    {
        _table.clear();
        Node_raw_pointer x{_head};
        auto max_order = 0;
        _min = _head;
        Node_raw_pointer y{nullptr};
        Node_raw_pointer z{nullptr};
        do {
            y = x;
            x = x->_next;
            z = _table[y->_order];
            while (z != nullptr) {
                _table.erase(y->_order);
                if (greater(y->_key, z->_key)) {
                    link(y, z);
                    y = z;
                } else {
                    link(z, y);
                }
                z = _table[y->_order];
            }
            _table[y->_order] = y;
            if (y->_order > max_order) { max_order = y->_order; }
        } while (x != _head);

        _head = nullptr;

        for (auto p : _table) {
            auto n = p.second;
            if (n != nullptr) {
                _min = greater(_min->_key, n.key) ? n : _min;
                _head = insert(n, _head);
            }
        }
    }

    Node_raw_pointer insert(Node_raw_pointer x, Node_raw_pointer head)
    {
        if (head == nullptr) {
            x->_prev = x;
            x->_prev = x;
        } else {
            head->_prev->_next = x;
            x->_next = head;
            x->_prev = head->_prev;
            head->_prev = x;
        }
        return x;
    }

    Node_raw_pointer cut(Node_raw_pointer x, Node_raw_pointer head)
    {
        if (x->_next == x) {
            x->_next = nullptr;
            x->_prev = nullptr;
            return nullptr;
        } else {
            x->_next->_prev = x->_prev;
            x->_prev->_next = x->_next;
            Node_raw_pointer res = x->_next;
            x->_next = nullptr;
            x->_prev = nullptr;
            if (head == x) { return res; }
            else { return head; }
        }
    }

    Node_raw_pointer meld(Node_raw_pointer x, Node_raw_pointer y)
    {
        if (x == nullptr) { return y; }
        if (y == nullptr) { return x; }
        x->_prev->_next = y->_next;
        y->_next->_prev = x->_prev;
        x->_prev = y;
        y->_next = x;
        return x;
    }
};

#endif // FIBONACCI_MIN_PQ_H
