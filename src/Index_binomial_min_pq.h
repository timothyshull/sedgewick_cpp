#ifndef INDEX_BINOMIAL_MIN_PQ_H
#define INDEX_BINOMIAL_MIN_PQ_H

#include <memory>
#include "utility.h"

template<typename Key>
class Index_binomial_min_pq_node;

template<typename Key, typename Comparator = Index_binomial_min_pq_key_comparator <Key>>
class Index_binomial_min_pq_iterator;

template<typename T>
struct Index_binomial_min_pq_key_comparator;

template<typename Key, typename Comparator = Index_binomial_min_pq_key_comparator<Key>>
class Index_binomial_min_pq;

template<typename Key>
class Index_binomial_min_pq_node {
public:
    using Key_type = Key;
    using Node = Index_binomial_min_pq_node<Key>;
    using Raw_node_pointer = Node*;
    using Owning_node_pointer = Node*;

    Index_binomial_min_pq_node() = default;

    Index_binomial_min_pq_node(const Index_binomial_min_pq_node&) = default;

    Index_binomial_min_pq_node(Index_binomial_min_pq_node&&) = default;

    Index_binomial_min_pq_node& operator=(const Index_binomial_min_pq_node&) = default;

    Index_binomial_min_pq_node& operator=(Index_binomial_min_pq_node&&) = default;

    ~Index_binomial_min_pq_node() = default;

    inline int index() const noexcept { return _index; }

private:
    Key_type _key;
    int _order;
    int _index;
    Raw_node_pointer _parent;
    Owning_node_pointer _child;
    Raw_node_pointer _sibling;

    template<typename, typename>
    friend class Index_binomial_min_pq;

    template<typename, typename>
    friend class Index_binomial_min_pq_iterator;
};

template<typename Key, typename Comparator>
class Index_binomial_min_pq_iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using Key_type = Key;
    using Node = Index_binomial_min_pq_node<Key>;
    using Raw_node_pointer = Node*;
    using Owning_node_pointer = Node*;
    using Comparator_type = Comparator;
    using Raw_key_pointer = Key_type*;
    using Priority_queue_type = Index_binomial_min_pq<Key_type, Comparator_type>;
    using Priority_queue_pointer = Priority_queue_type*

    Index_binomial_min_pq_iterator(Priority_queue_type& pq) : _data{pq._size}, _original{&pq}
    {
        _data._head = clone(pq._head, false, false, nullptr);
    }

    Index_binomial_min_pq_iterator(Priority_queue_type& pq, Raw_node_pointer n) : _data{pq._size}, _original{&pq}
    {
        _data._head = clone(n, false, false, nullptr);
    }

    inline bool has_next() const { return !_data.is_empty(); }

    int next()
    {
        if (!has_next()) { throw utility::No_such_element_exception{""}; }
        return _data.delete_min();
    }

    inline Key_type operator*() const
    {
        return _data._head->_key;
    }

    inline Raw_node_pointer operator->() const
    {
        return _data._head;
    }

    inline Index_binomial_min_pq_iterator& operator++()
    {
        if (has_next()) {
            next();
        }
        return *this;
    }

    inline Index_binomial_min_pq_iterator operator++(int)
    {
        Index_binomial_min_pq_iterator t{*this};
        ++(*this);
        return t;
    }

    friend
    inline bool operator==(const Index_binomial_min_pq_iterator& x, const Index_binomial_min_pq_iterator& y)
    {
        if (x._original != y._original) {
            return false;
        }
        if (x._data._head && y._data._head) {
            return *(x._data._head->_key) == *(y._data._head->_key);
        }
        return x._data._head == nullptr && y._data._head == nullptr;
    }

    friend
    inline bool operator!=(const Index_binomial_min_pq_iterator& x, const Index_binomial_min_pq_iterator& y) { return !(x == y); }

private:
    Priority_queue_type _data;
    Priority_queue_pointer _original;

    template<typename>
    friend class Index_binomial_min_pq;

    Raw_node_pointer clone(Raw_node_pointer x, bool is_parent, bool is_child, Raw_node_pointer parent)
    {
        if (x == nullptr) { return nullptr; }
        Raw_node_pointer node{new Index_binomial_min_pq_node<Key_type>};
        node->_index = x->_index;
        node->_key = x->_key;
        _data._nodes[node->_index] = node;
        node->_parent = parent;
        node->_sibling = clone(x->_sibling, false, false, parent);
        node->_child = clone(x->_child, false, true, node);
        return node;
    }
};

template<typename T>
struct Index_binomial_min_pq_key_comparator {
    bool operator()(const T& x, const T& y) const
    {
        return x < y;
    }
};

template<typename Key, typename Comparator>
class Index_binomial_min_pq {
public:
    using Key_type = Key;
    using Node = Index_binomial_min_pq_node<Key_type>;
    using Raw_node_pointer = Node*;
    using Owning_node_pointer = Node*;
    using Comparator_type = Comparator;
    using Iterator_type = Index_binomial_min_pq_iterator<Key_type>;

    inline Iterator_type begin() { return Iterator_type(*this); }

    inline Iterator_type end() { return Iterator_type(*this, nullptr); }

    Index_binomial_min_pq(int size)
            : _comp{},
              _nodes(static_cast<std::vector<Raw_node_pointer>::size_type>(size)),
              _size{size}
    {
        // will throw before
        // if (size < 0) { throw utility::Illegal_argument_exception("Cannot create a priority _queue of negative size"); }
    }

    inline bool is_empty() const noexcept { return _head == nullptr; }

    bool contains(int i) const
    {
        if (i < 0 || i >= _size) { throw utility::Index_out_of_bounds_exception{""}; }
        else { return _nodes[i] != nullptr; }
    }

    int size()
    {
        auto result = 0;
        int tmp;
        for (Raw_node_pointer node{_head}; node != nullptr; node = node->_sibling) {
            if (node->_order > 30) {
                throw utility::Arithmetic_exception{"The number of elements cannot be evaluated, but the priority queue is still valid."};
            }
            tmp = 1 << node->_order;
            result |= tmp;
        }
        return result;
    }

    void insert(int i, Key_type& key)
    {
        if (i < 0 || i >= _size) { throw utility::Index_out_of_bounds_exception{}; }
        if (contains(i)) { throw utility::Illegal_argument_exception("Specified index is already in the queue"); }
        Raw_node_pointer x{new Index_binomial_min_pq_node<Key_type>};
        x->_key = key;
        x->_index = i;
        x->_order = 0;
        _nodes[i] = x;
        Index_binomial_min_pq<Key_type, Comparator_type> tmp{};
        tmp._head = x;
        _head = create_union(tmp)._head;
    }

    int min_index()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Priority queue is empty"}; }
        Raw_node_pointer min{_head};
        Raw_node_pointer current{_head};
        while (current->_sibling != nullptr) {
            min = (_greater(min->_key, current->_sibling->_key)) ? current->_sibling : min;
            current = current->_sibling;
        }
        return min->_index;
    }

    Key min_key()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Priority queue is empty"}; }
        Raw_node_pointer min{_head};
        Raw_node_pointer current{_head};
        while (current->_sibling != nullptr) {
            min = (_greater(min->_key, current->_sibling->_key)) ? current->_sibling : min;
            current = current->_sibling;
        }
        return min->_key;
    }

    int delete_min()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Priority _queue is empty"}; }
        Raw_node_pointer min{_erase_min()};
        Raw_node_pointer x{(min->_child == nullptr) ? min : min->_child};
        if (min->_child != nullptr) {
            min->_child = nullptr;
            Raw_node_pointer prev_x{nullptr};
            Raw_node_pointer next_x{x->_sibling};
            while (next_x != nullptr) {
                // TODO: need some sort of delete call here
                x->_parent = nullptr;
                x->_sibling = prev_x;
                prev_x = x;
                x = next_x;
                next_x = next_x->_sibling;
            }
            x->_parent = nullptr;
            x->_sibling = prev_x;
            Index_binomial_min_pq<Key_type, Comparator_type> tmp{};
            tmp._head = x;
            _head = create_union(tmp)._head;
        }
        return min->_index;
    }

    Key key_of(int i)
    {
        if (i < 0 || i >= _size) { throw utility::Index_out_of_bounds_exception{""}; }
        if (!contains(i)) { throw utility::Illegal_argument_exception("Specified index is not _in the _queue"); }
        return _nodes[i].key;
    }

    void change_key(int i, Key_type& key)
    {
        if (i < 0 || i >= _size) { throw utility::Index_out_of_bounds_exception{""}; }
        if (!contains(i)) { throw utility::Illegal_argument_exception("Specified index is not _in the _queue"); }
        if (_greater(_nodes[i].key, key)) { decrease_key(i, key); }
        else { increase_key(i, key); }
    }

    void decrease_key(int i, Key_type& key)
    {
        if (i < 0 || i >= _size) { throw utility::Index_out_of_bounds_exception{""}; }
        if (!contains(i)) { throw utility::No_such_element_exception{"Specified index is not _in the _queue"}; }
        if (_greater(key, _nodes[i].key)) {
            throw utility::Illegal_argument_exception("Calling with this argument would not decrease the key");
        }
        Raw_node_pointer x{_nodes[i]};
        x->_key = key;
        _swim(i);
    }

    void increase_key(int i, Key_type& key)
    {
        if (i < 0 || i >= _size) { throw utility::Index_out_of_bounds_exception{""}; }
        if (!contains(i)) { throw utility::No_such_element_exception{"Specified index is not _in the _queue"}; }
        if (_greater(_nodes[i].key, key)) {
            throw utility::Illegal_argument_exception("Calling with this argument would not increase the key");
        }
        remove(i);
        insert(i, key);
    }

    void remove(int i)
    {
        if (i < 0 || i >= _size) { throw utility::Index_out_of_bounds_exception{""}; }
        if (!contains(i)) { throw utility::No_such_element_exception{"Specified index is not _in the _queue"}; }
        _to_the_root(i);
        Raw_node_pointer x = erase(i);
        if (x->_child != nullptr) {
            Raw_node_pointer y = x;
            x = x->_child;
            y->_child = nullptr;
            Raw_node_pointer prevx = nullptr, nextx = x->_sibling;
            while (nextx != nullptr) {
                x->_parent = nullptr;
                x->_sibling = prevx;
                prevx = x;
                x = nextx;
                nextx = nextx->_sibling;
            }
            x->_parent = nullptr;
            x->_sibling = prevx;
            Index_binomial_min_pq<Key_type, Comparator_type> tmp{};
            tmp._head = x;
            _head = create_union(tmp)._head;
        }
    }

private:
    Owning_node_pointer _head;
    std::vector<Raw_node_pointer> _nodes;
    int _size;
    Comparator_type _comp;

    template<typename, typename>
    friend class Index_binomial_min_pq_iterator;

    template<typename, typename>
    friend class Index_binomial_min_pq_reverse_iterator;

    bool _greater(Key_type& n, Key_type& m)
    {
        return Comparator{}(m, n);
    }

    void _exchange(Raw_node_pointer x, Raw_node_pointer y)
    {
        Key_type temp_key{x->_key};
        x->_key = y->_key;
        y->_key = temp_key;

        auto temp_int = x->_index;
        x->_index = y->_index;
        y->_index = temp_int;
        _nodes[x->_index] = x;
        _nodes[y->_index] = y;
    }

    void _link(Raw_node_pointer root1, Raw_node_pointer root2)
    {
        root1->_sibling = root2->_child;
        root1->_parent = root2;
        root2->_child = root1;
        root2->_order++;
    }

    void _swim(int i)
    {
        Raw_node_pointer x = _nodes[i];
        Raw_node_pointer parent = x->_parent;
        if (parent != nullptr && _greater(parent->_key, x->_key)) {
            _exchange(x, parent);
            _swim(i);
        }
    }

    void _to_the_root(int i)
    {
        Raw_node_pointer x = _nodes[i];
        Raw_node_pointer parent = x->_parent;
        if (parent != nullptr) {
            _exchange(x, parent);
            _to_the_root(i);
        }
    }

    Raw_node_pointer erase(int i)
    {
        Raw_node_pointer reference = _nodes[i];
        Raw_node_pointer x = _head;
        Raw_node_pointer previous = nullptr;
        while (x != reference) {
            previous = x;
            x = x->_sibling;
        }
        if (previous) {
            previous->_sibling = x->_sibling;
        }
        if (x == _head) { _head = _head->_sibling; }
        _nodes[i] = nullptr;
        return x;
    }

    Raw_node_pointer _erase_min()
    {
        Raw_node_pointer min = _head;
        Raw_node_pointer previous = nullptr;
        Raw_node_pointer current = _head;
        while (current->_sibling != nullptr) {
            if (_greater(min->_key, current->_sibling->_key)) {
                previous = current;
                min = current->_sibling;
            }
            current = current->_sibling;
        }
        if (previous) {
            previous->_sibling = min->_sibling;
        }
        if (min == _head) { _head = min->_sibling; }
        _nodes[min->_index] = nullptr;
        return min;
    }

    Raw_node_pointer _merge(Raw_node_pointer h, Raw_node_pointer x, Raw_node_pointer y)
    {
        if (x == nullptr && y == nullptr) { return h; }
        else if (x == nullptr) { h->_sibling = _merge(y, nullptr, y->_sibling); }
        else if (y == nullptr) { h->_sibling = _merge(x, x->_sibling, nullptr); }
        else if (x->_order < y->_order) { h->_sibling = _merge(x, x->_sibling, y); }
        else { h->_sibling = _merge(y, x, y->_sibling); }
        return h;
    }

    Index_binomial_min_pq<Key_type, Comparator_type>& create_union(Index_binomial_min_pq<Key_type, Comparator_type>& heap)
    {
        _head = _merge(new Index_binomial_min_pq_node<Key_type>, _head, heap._head)->_sibling;
        Raw_node_pointer x{_head};
        Raw_node_pointer prev_x{nullptr};
        Raw_node_pointer next_x{x->_sibling};
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
                    _head = next_x;
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
};

#endif // INDEX_BINOMIAL_MIN_PQ_H
