#ifndef INDEX_FIBONACCI_MIN_PQ_H
#define INDEX_FIBONACCI_MIN_PQ_H

#include <iterator>
#include <unordered_map>
#include "utility.h"

template<typename Key>
class Index_fibonacci_min_pq_node;

template<typename T>
struct Index_fibonacci_min_pq_key_comparator;

template<typename Key, typename Comparator = Index_fibonacci_min_pq_key_comparator<Key>>
class Index_fibonacci_min_pq_iterator;

template<typename Key, typename Comparator = Index_fibonacci_min_pq_key_comparator<Key>>
class Index_fibonacci_min_pq;

template<typename Key>
class Index_fibonacci_min_pq_node {
public:
    using Key_type = Key;
    using Node = Index_fibonacci_min_pq_node<Key>;
    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;

private:
    Key_type _key;
    int _order;
    int _index;
    bool _mark;
    Raw_node_pointer _prev;
    Raw_node_pointer _next;
    Raw_node_pointer _parent;
    Owning_node_pointer _child;

    template<typename, typename, typename>
    friend class Index_fibonacci_min_pq;

    template<typename, typename>
    friend class Index_fibonacci_min_pq_iterator;
};

template<typename Key, typename Comparator>
class Index_fibonacci_min_pq_iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using Key_type = Key;
    using Node = Index_fibonacci_min_pq_node<Key>;
    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;
    using Comparator_type = Comparator;
    using Priority_queue_type = Index_fibonacci_min_pq<Key_type, Comparator_type>;
    using Priority_queue_pointer = Priority_queue_type*;

    Index_fibonacci_min_pq_iterator(Priority_queue_type& pq) : _copy{pq._num}, _original{&pq}
    {
        for (auto x : pq._nodes) {
            if (x != nullptr) { _copy.insert(x->index, x->key); }
        }
    }

    Index_fibonacci_min_pq_iterator(Priority_queue_type& pq, Raw_node_pointer n) : _copy{pq._num}, _original{&pq}
    {
        // TODO: this may cause issues
        for (auto x : pq._nodes) {
            if (x != nullptr) { _copy.insert(x->index, x->key); }
        }
        _copy._head = n;
    }

    inline bool has_next() const noexcept { return !_copy.is_empty(); }

    int next()
    {
        if (!has_next()) { throw utility::No_such_element_exception{""}; }
        return _copy.delete_min();
    }

    inline Key_type operator*() const
    {
        return _copy._head->_key;
    }

    inline Raw_node_pointer operator->() const
    {
        return _copy._head;
    }

    inline Index_fibonacci_min_pq_iterator& operator++()
    {
        if (has_next()) {
            next();
        }
        return *this;
    }

    inline Index_fibonacci_min_pq_iterator operator++(int)
    {
        Index_fibonacci_min_pq_iterator t{*this};
        ++(*this);
        return t;
    }

    friend
    inline bool operator==(const Index_fibonacci_min_pq_iterator& x, const Index_fibonacci_min_pq_iterator& y)
    {
        if (x._original != y._original) {
            return false;
        }
        if (x._copy._head && y._copy._head) {
            return *(x._copy._head->_key) == *(y._copy._head->_key);
        }
        return x._copy._head == nullptr && y._copy._head == nullptr;
    }

    friend
    inline bool operator!=(const Index_fibonacci_min_pq_iterator& x, const Index_fibonacci_min_pq_iterator& y) { return !(x == y); }

private:
    Priority_queue_type _copy;
    Priority_queue_pointer _original;

    template<typename>
    friend class Index_fibonacci_min_pq;
};

template<typename T>
struct Index_fibonacci_min_pq_key_comparator {
    int operator()(const T& x, const T& y) const
    {
        return x < y;
    }
};

template<typename Key, typename Comparator>
class Index_fibonacci_min_pq {
public:
    using Key_type = Key;
    using Node = Index_fibonacci_min_pq_node<Key>;
    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;
    using Comparator_type = Comparator;
    using Iterator_type = Index_fibonacci_min_pq_iterator<Key_type, Comparator_type>;

    inline Iterator_type begin() { return Iterator_type(*this); }

    inline Iterator_type end() { return Iterator_type(*this, nullptr); }

    Index_fibonacci_min_pq(int size)
            : _num{size},
              _nodes(static_cast<std::vector<Raw_node_pointer>::size_type>(size)),
              _comp{}
    {
        // will throw before this
        // if (size < 0) { throw utility::Illegal_argument_exception("Cannot create a priority _queue of negative size"); }
    }

    inline bool is_empty() const noexcept { return _size == 0; }

    bool contains(int i)
    {
        if (i < 0 || i >= _num) { throw utility::Index_out_of_bounds_exception{""}; }
        else { return _nodes[i] != nullptr; }
    }

    inline int size() const noexcept { return _size; }

    void insert(int i, Key key)
    {
        if (i < 0 || i >= _num) { throw utility::Index_out_of_bounds_exception{""}; }
        if (contains(i)) { throw utility::Illegal_argument_exception("Specified index is already _in the _queue"); }
        Raw_node_pointer x = new Index_fibonacci_min_pq_node<Key_type>();
        x->_key = key;
        x->_index = i;
        _nodes[i] = x;
        ++_size;
        _head = _insert(x, _head);
        if (_min == nullptr) { _min = _head; }
        else { _min = (_greater(_min->_key, key)) ? _head : _min; }
    }

    int min_index() const
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Priority _queue is empty"}; }
        return _min->_index;
    }

    Key_type min_key()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Priority _queue is empty"}; }
        return _min->_key;
    }

    int delete_min()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Priority _queue is empty"}; }
        _head = _cut(_min, _head);
        Raw_node_pointer x = _min->_child;
        int index = _min->_index;
        _min->_key = nullptr;
        if (x != nullptr) {
            do {
                x->_parent = nullptr;
                x = x->_next;
            } while (x != _min->_child);
            _head = _meld(_head, x);
            _min->_child = nullptr;
        }
        _size--;
        if (!is_empty()) { _consolidate(); }
        else { _min = nullptr; }
        _nodes[index] = nullptr;
        return index;
    }

    Key_type key_of(int i)
    {
        if (i < 0 || i >= _num) { throw utility::Index_out_of_bounds_exception{""}; }
        if (!contains(i)) { throw utility::No_such_element_exception{"Specified index is not _in the _queue"}; }
        return _nodes[i]->key;
    }

    void change_key(int i, Key_type& key)
    {
        if (i < 0 || i >= _num) { throw utility::Index_out_of_bounds_exception{""}; }
        if (!contains(i)) { throw utility::No_such_element_exception{"Specified index is not _in the _queue"}; }
        if (_greater(key, _nodes[i]->key)) { increase_key(i, key); }
        else { decrease_key(i, key); }
    }

    void decrease_key(int i, Key_type& key)
    {
        if (i < 0 || i >= _num) { throw utility::Index_out_of_bounds_exception{""}; }
        if (!contains(i)) { throw utility::No_such_element_exception{"Specified index is not _in the _queue"}; }
        if (_greater(key, _nodes[i]->key)) {
            throw utility::Illegal_argument_exception("Calling with this argument would not decrease the key");
        }
        Raw_node_pointer x = _nodes[i];
        x->_key = key;
        if (_greater(_min->_key, key)) { _min = x; }
        if (x->_parent != nullptr && _greater(x->_parent->_key, key)) {
            _cut(i);
        }
    }

    void increase_key(int i, Key_type& key)
    {
        if (i < 0 || i >= _num) { throw utility::Index_out_of_bounds_exception{""}; }
        if (!contains(i)) { throw utility::No_such_element_exception{"Specified index is not _in the _queue"}; }
        if (_greater(_nodes[i]->key, key)) {
            throw utility::Illegal_argument_exception("Calling with this argument would not increase the key");
        }
        delete (i);
        insert(i, key);
    }

    void remove(int i)
    {
        if (i < 0 || i >= _num) { throw utility::Index_out_of_bounds_exception{""}; }
        if (!contains(i)) { throw utility::No_such_element_exception{"Specified index is not _in the _queue"}; }
        Raw_node_pointer x = _nodes[i];
        x->_key = nullptr;
        if (x->_parent != nullptr) {
            _cut(i);
        }
        _head = _cut(x, _head);
        if (x->_child != nullptr) {
            Raw_node_pointer child = x->_child;
            x->_child = nullptr;
            x = child;
            do {
                child->_parent = nullptr;
                child = child->_next;
            } while (child != x);
            _head = _meld(_head, child);
        }
        if (!is_empty()) { _consolidate(); }
        else { _min = nullptr; }
        _nodes[i] = nullptr;
        _size--;
    }

private:
    Raw_node_pointer _head;
    Raw_node_pointer _min;
    std::vector<Raw_node_pointer> _nodes;
    int _size;
    int _num;
    Comparator_type _comp;
    std::unordered_map<int, Raw_node_pointer> _table;

    template<typename, typename>
    friend class Index_fibonacci_min_pq_iterator;

    template<typename, typename>
    friend class Index_fibonacci_min_pq_reverse_iterator;

    bool _greater(Key_type& n, Key_type& m)
    {
        if (n == nullptr) { return false; }
        if (m == nullptr) { return true; }
        return _comp.compare(n, m) > 0;
    }

    void _link(Raw_node_pointer root1, Raw_node_pointer root2)
    {
        root1->_parent = root2;
        root2->_child = _insert(root1, root2->_child);
        root2->_order++;
    }

    void _cut(int i)
    {
        Raw_node_pointer x = _nodes[i];
        Raw_node_pointer parent = x->_parent;
        parent->_child = _cut(x, parent->_child);
        x->_parent = nullptr;
        parent->_order--;
        _head = _insert(x, _head);
        parent->_mark = !parent->_mark;
        if (!parent->_mark && parent->_parent != nullptr) {
            _cut(parent->_index);
        }
    }

    void _consolidate()
    {
        _table.clear();
        Raw_node_pointer x = _head;
        int maxOrder = 0;
        _min = _head;
        Raw_node_pointer y = nullptr, z = nullptr;
        do {
            y = x;
            x = x->_next;
            z = _table[y->_order];
            while (z != nullptr) {
                _table.erase(y->_order);
                if (_greater(y->_key, z->_key)) {
                    _link(y, z);
                    y = z;
                } else {
                    _link(z, y);
                }
                z = _table[y->_order];
            }
            _table.insert({y->_order, y});
            if (y->_order > maxOrder) { maxOrder = y->_order; }
        } while (x != _head);
        _head = nullptr;
        for (auto n : _table) {
            _min = _greater(_min->_key, n.second->_key) ? n.second : _min;
            _head = _insert(n.second, _head);
        }
    }

    Raw_node_pointer _insert(Raw_node_pointer x, Raw_node_pointer head)
    {
        if (head == nullptr) {
            x->_prev = x;
            x->_next = x;
        } else {
            head->_prev->_next = x;
            x->_next = head;
            x->_prev = head->_prev;
            head->_prev = x;
        }
        return x;
    }

    Raw_node_pointer _cut(Raw_node_pointer x, Raw_node_pointer head)
    {
        if (x->_next == x) {
            x->_next = nullptr;
            x->_prev = nullptr;
            return nullptr;
        } else {
            x->_next->_prev = x->_prev;
            x->_prev->_next = x->_next;
            Raw_node_pointer res = x->_next;
            x->_next = nullptr;
            x->_prev = nullptr;
            if (head == x) { return res; }
            else { return head; }
        }
    }

    Raw_node_pointer _meld(Raw_node_pointer x, Raw_node_pointer y)
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

#endif // INDEX_FIBONACCI_MIN_PQ_H
