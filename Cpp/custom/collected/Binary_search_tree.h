#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <cstddef>
#include <algorithm>
#include <sstream>
#include <vector>

#include "Queue.h"
#include "utility.h"
#include "Std_out.h"

template<typename Key, typename Value>
class Binary_search_tree_node;

template<typename Key, typename Value>
class Binary_search_tree_iterator;

template<typename Key, typename Value>
class Binary_search_tree_reverse_iterator;

template<typename T>
struct Binary_search_tree_key_comparator;

template<typename Key, typename Value, typename Comparator = Binary_search_tree_key_comparator<Key>>
class Binary_search_tree;

template<typename Key, typename Value>
struct Binary_search_tree_node_pointer_traits {
    using Key_type = Key;
    using Value_type = Value;

    using Node_type = Binary_search_tree_node<Key_type, Value_type>;
    using Node_raw_pointer = Binary_search_tree_node<Key_type, Value_type>*;
    using Node_owning_pointer = std::unique_ptr<Node_type>;
    using Node_shared_pointer = std::shared_ptr<Node_type>;
    using Shared_value_pointer = std::shared_ptr<Value_type>;
    using Shared_key_pointer = std::shared_ptr<Key_type>;
    using Size_type = std::size_t;
};

template<typename Key, typename Value>
class Binary_search_tree_node {
public:
    using Node_traits = Binary_search_tree_node_pointer_traits<Key, Value>;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;
    using Node_type = typename Node_traits::Node_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Node_shared_pointer = typename Node_traits::Node_shared_pointer;
    using Shared_value_pointer = typename Node_traits::Shared_value_pointer;
    using Shared_key_pointer = std::shared_ptr<Key_type>;
    using Size_type = typename Node_traits::Size_type;

    Binary_search_tree_node(Key_type& key, Value_type& val, int size) : _key{std::make_shared<Key_type>(key)}, _value{std::make_shared<Value_type>(val)}, _size{size}, _height{height} {}

private:
    // TODO: redo the implementations that require optional key return values to avoid this
    Shared_key_pointer _key;
    Shared_value_pointer _value;

    int _size;

    Node_owning_pointer _left;
    Node_owning_pointer _right;

    // ~Binary_search_tree_node() = delete;

    // Binary_search_tree_node(Binary_search_tree_node const&) = delete;

    // Binary_search_tree_node& operator=(Binary_search_tree_node const&) = delete;

    template<typename, typename, typename>
    friend class Binary_search_tree;

    template<typename, typename>
    friend class Binary_search_tree_iterator;

    template<typename, typename>
    friend class Binary_search_tree_reverse_iterator;
};

// this is implemented in a way that will invalidate the iterator easily
// and it takes N * size extra space
// this is due to the fact that the nodes do not have parent pointers
template<typename Key, typename Value>
class Binary_search_tree_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using Node_traits = Binary_search_tree_node_pointer_traits<Key, Value>;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Tree_type = Binary_search_tree<Key_type, Value_type>;
    using Tree_pointer = Tree_type*;

    using Reference_type = Value_type&;

    Binary_search_tree_iterator() noexcept = delete;

    explicit Binary_search_tree_iterator(Tree_pointer tree) noexcept : _index{0}, _tree{tree}
    {
        _construct_in_order(_tree->_get_root());
    }

    Binary_search_tree_iterator(Tree_pointer tree, int index) noexcept : _index{index}, _tree{tree}
    {
        _construct_in_order(_tree->_get_root());
        if (index > _in_order.size()) {
            throw utility::Illegal_argument_exception("The index is out of range");
        }
    }

    inline Node_raw_pointer operator*() const
    {
        return _in_order[_index];
    }

    inline Node_raw_pointer operator->() const
    {
        return _in_order[_index];
    }

    inline Binary_search_tree_iterator& operator++()
    {
        ++_index;
        if (_index >= _in_order.size()) {
            _index = -1;
        }
        return *this;
    }

    inline Binary_search_tree_iterator operator++(int)
    {
        Binary_search_tree_iterator t{*this};
        ++(*this);
        return t;
    }

    inline Binary_search_tree_iterator& operator--()
    {
        if (_index > 0) {
            --_index;
        }
        return *this;
    }

    inline Binary_search_tree_iterator operator--(int)
    {
        Binary_search_tree_iterator t{*this};
        --(*this);
        return t;
    }

    Node_raw_pointer operator[](const int& index)
    {
        return _in_order[index];
    }

    friend
    inline bool operator==(const Binary_search_tree_iterator& x, const Binary_search_tree_iterator& y)
    {
        return x._in_order == y._in_order && x._index == y._index;
    }

    friend
    inline bool operator!=(const Binary_search_tree_iterator& x, const Binary_search_tree_iterator& y) { return !(x == y); }

private:
    int _index;
    std::vector<Node_raw_pointer> _in_order;
    Tree_pointer _tree;

    template<typename>
    friend class Binary_search_tree;

    void _construct_in_order(Node_raw_pointer x)
    {
        if (x == nullptr) {
            return;
        }
        _in_order.reserve(x->_size);
        _construct_in_order(x->_left.get());
        _in_order.emplace_back(x);
        _construct_in_order(x->_right.get());
    }

};

template<typename Key, typename Value>
class Binary_search_tree_reverse_iterator {
    using iterator_category = std::random_access_iterator_tag;
    using Node_traits = Binary_search_tree_node_pointer_traits<Key, Value>;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Tree_type = Binary_search_tree<Key_type, Value_type>;
    using Tree_pointer = Tree_type*;

    Binary_search_tree_reverse_iterator() noexcept = delete;

    explicit Binary_search_tree_reverse_iterator(Tree_pointer tree) noexcept : _index{0}, _tree{tree}
    {
        _construct_in_order(_tree->_get_root());
    }

    Binary_search_tree_reverse_iterator(Tree_pointer tree, int index) noexcept : _index{index}, _tree{tree}
    {
        _construct_in_order(_tree->_get_root());
        if (index > _in_order.size()) {
            throw utility::Illegal_argument_exception("The index is out of range");
        }
    }

    inline Node_raw_pointer operator*() const
    {
        return _in_order[_index];
    }

    inline Node_raw_pointer operator->() const
    {
        return _in_order[_index];
    }

    inline Binary_search_tree_reverse_iterator& operator++()
    {
        ++_index;
        if (_index >= _in_order.size()) {
            _index = -1;
        }
        return *this;
    }

    inline Binary_search_tree_reverse_iterator operator++(int)
    {
        Binary_search_tree_reverse_iterator t{*this};
        ++(*this);
        return t;
    }

    inline Binary_search_tree_reverse_iterator& operator--()
    {
        if (_index > 0) {
            --_index;
        }
        return *this;
    }

    inline Binary_search_tree_reverse_iterator operator--(int)
    {
        Binary_search_tree_reverse_iterator t{*this};
        --(*this);
        return t;
    }

    Node_raw_pointer operator[](const int& index)
    {
        return _in_order[index];
    }

    friend
    inline bool operator==(const Binary_search_tree_reverse_iterator& x, const Binary_search_tree_reverse_iterator& y)
    {
        return x._in_order == y._in_order && x._index == y._index;
    }

    friend
    inline bool operator!=(const Binary_search_tree_reverse_iterator& x, const Binary_search_tree_reverse_iterator& y) { return !(x == y); }

private:
    int _index;
    std::vector<Node_raw_pointer> _in_order;
    Tree_pointer _tree;

    template<typename>
    friend class Binary_search_tree;

    void _construct_in_order(Node_raw_pointer x)
    {
        if (x == nullptr) {
            return;
        }
        _in_order.reserve(x->_size);
        _construct_in_order(x->_right.get());
        _in_order.emplace_back(x);
        _construct_in_order(x->_left.get());
    }

};

template<typename T>
struct Binary_search_tree_key_comparator {
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

template<typename Key, typename Value, typename Comparator>
class Binary_search_tree {
public:
    using Node_traits = Binary_search_tree_node_pointer_traits<Key, Value>;
    using Node_type = typename Node_traits::Node_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Node_shared_pointer = typename Node_traits::Node_shared_pointer;
    using Shared_value_pointer = typename Node_traits::Shared_value_pointer;
    using Shared_key_pointer = typename Node_traits::Shared_key_pointer;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;
    using Comparator_type = Comparator;

    using Reference_type = Value_type&;
    using Const_reference_type = const Value_type&;
    using Pointer_type = Value_type*;
    using Const_pointer_type = Value_type const*;
    using Size_type = std::size_t;
    using Difference_type = std::ptrdiff_t;  // TODO: check on this because of the relationship with max_size
    using Iterator_type = Binary_search_tree_iterator<Key_type, Value_type>;
    using Reverse_iterator_type = Binary_search_tree_reverse_iterator<Key_type, Value_type>;

    inline bool is_empty() const { return _root == nullptr; }

    inline int size() const { return _size(_get_root()); }

    inline int height() const { return _height(_get_root()); }

    Iterator_type begin() { return Iterator_type(this, 0); }

    Iterator_type end() { return Iterator_type(this, -1); }

    Reverse_iterator_type rbegin() { return Reverse_iterator_type(this, 0); }

    Reverse_iterator_type rend() { return Reverse_iterator_type(this, -1); };
    // void clear();

    Shared_value_pointer get(Key_type key) const
    {
        Node_raw_pointer n = _get(_get_root(), key);
        if (n == nullptr) {
            return nullptr;
        }
        return n->_value;
    }

    inline bool contains(Key_type key) const { return get(key) != nullptr; }

    void put(Key_type key, Value_type& val)
    {
        _root = std::unique_ptr<Node_type>{_put(_get_root(), key, val)};
        utility::assert(_check(), "Binary_search_tree invariant check failed after \"put()\"");
    }

    void delete_min()
    {
        if (is_empty()) {
            throw utility::No_such_element_exception("The method \"delete_min()\" was called on an empty symbol table");
        }
        _root = _delete_min(_get_root());
        utility::assert(_check(), "Binary_search_tree invariant check failed after \"delete_min()\"");
    }

    void delete_max()
    {
        if (is_empty()) {
            throw utility::No_such_element_exception("The method \"delete_max()\" was called on an empty symbol table");
        }
        _root = _delete_max(_get_root());
        utility::assert(_check(), "Binary_search_tree invariant check failed after \"delete_max()\"");
    }

    Key_type min() const
    {
        if (is_empty()) {
            throw utility::No_such_element_exception("The method \"min()\" was called on an empty symbol table");
        }
        return *(_min(_get_root())->_key);
    }

    Key_type max() const
    {
        if (is_empty()) {
            throw utility::No_such_element_exception("The method \"max()\" was called on an empty symbol table");
        }
        return *(_max(_get_root())->_key);
    }

    // TODO: may need to wrap keys in shared_ptr also
    Key_type floor(Key_type key) const
    {
        if (is_empty()) {
            throw utility::No_such_element_exception("The method \"floor()\" was called on an empty symbol table");
        }
        Node_raw_pointer x = _floor(_get_root(), key);
        if (x == nullptr) {
            return nullptr;
        } else {
            return x->_key;
        }
    }

    Shared_key_pointer ceiling(Key_type key) const
    {
        if (is_empty()) {
            throw utility::No_such_element_exception("The method \"ceiling()\" was called on an empty symbol table");
        }
        Node_raw_pointer x = _ceiling(_get_root(), key);
        if (x == nullptr) {
            return nullptr;
        } else {
            return x->_key;
        }
    }

    Shared_key_pointer select(int k) const
    {
        if (k < 0 || k >= size()) {
            std::stringstream ss;
            ss << "The argument \"k\" is not in the range 0-" << size() - 1;
            throw utility::Illegal_argument_exception(ss.str());
        }
        Node_raw_pointer x = _select(_get_root(), k);
        if (x == nullptr) {
            return nullptr;
        } else {
            return x->_key;
        }
    }

    int rank(Key_type key) const
    {
        return _rank(key, _get_root());
    }

    Queue<Key_type> keys() const { return keys_in_order(); }

    Queue<Key_type> keys_in_order() const
    {
        Queue<Key_type> queue;
        _keys_in_order(_get_root(), queue);
        return queue;
    }

    Queue<Key_type> keys_in_level_order() const
    {
        Queue<Key_type> queue;
        if (!is_empty()) {
            Queue<Node_raw_pointer> queue2;
            queue2.enqueue(_get_root());
            while (!queue.is_empty()) {
                Node_raw_pointer x = queue2.dequeue();
                queue.enqueue(x->_key);
                if (x->_left != nullptr) {
                    queue2.enqueue(x->_left.get());
                }
                if (x->_right != nullptr) {
                    queue2.enqueue(x->_right.get());
                }
            }
        }
        return queue;
    }

    Queue<Key_type> keys(Key_type lo, Key_type hi) const
    {
        Queue<Key_type> queue;
        _keys(_get_root(), queue, lo, hi);
        return queue;
    }

    int size(Key_type lo, Key_type hi) const
    {
        if (Comparator_type()(lo, hi) > 0) {
            return 0;
        }
        if (contains(hi)) {
            return rank(hi) - rank(lo) + 1;
        } else {
            return rank(hi) - rank(lo);
        }
    }

private:
    Node_owning_pointer _root;

    template<typename, typename>
    friend class Binary_search_tree_iterator;

    template<typename, typename>
    friend class Binary_search_tree_reverse_iterator;

    inline const Node_raw_pointer _get_root() const { return _root.get(); }

    const Node_raw_pointer _get_head() const {}

    const Node_raw_pointer _get_tail() const {}

    int _size(Node_raw_pointer n) const
    {
        if (n == nullptr) {
            return 0;
        }
        return n->_size;
    }

    int _height(Node_raw_pointer n) const
    {
        if (n == nullptr) {
            return 0;
        }
        return n->_height;
    }

    Node_raw_pointer _get(Node_raw_pointer n, Key_type key) const
    {
        if (n == nullptr) {
            return nullptr;
        }
        if (Comparator_type()(key, *(n->_key))) {
            return _get(n->_left.get(), key);
        } else if (Comparator_type()(*(n->_key), key)) {
            return _get(n->_right.get(), key);
        } else {
            return n;
        }
    }

    Node_raw_pointer _put(Node_raw_pointer x, Key_type key, Value_type val)
    {
        if (x == nullptr) {
            // TODO: use Node_type
            return new Binary_search_tree_node<Key_type, Value_type>(key, val, 0, 1);
        }
        int cmp = Comparator_type()(key, *(x->_key));
        if (cmp < 0) {
            x->_left = std::unique_ptr<Node_type>{_put(x->_left.get(), key, val)};
        } else if (cmp > 0) {
            x->_right = std::unique_ptr<Node_type>{_put(x->_right.get(), key, val)};
        } else {
            x->_value = std::make_shared<Value_type>(val);
            return x;
        }
        x->_size = 1 + _size(x->_left.get()) + _size(x->_right.get());
        x->_height = 1 + std::max(_height(x->_left.get()), _height(x->_right.get()));
        return _balance(x);
    }

    Node_raw_pointer _balance(Node_raw_pointer x)
    {
        if (_balance_factor(x) < -1) {
            if (_balance_factor(x->_right.get()) > 0) {
                x->_right = std::unique_ptr<Node_type>{_rotate_right(x->_right.get())};
            }
            x = _rotate_left(x);
        } else if (_balance_factor(x) > 1) {
            if (_balance_factor(x->_left.get()) < 0) {
                x->_left = std::unique_ptr<Node_type>{_rotate_left(x->_left.get())};
            }
            x = _rotate_right(x);
        }
        return x;
    }

    int _balance_factor(Node_raw_pointer x) const { return _height(x->_left.get()) - _height(x->_right.get()); }

    Node_raw_pointer _rotate_right(Node_raw_pointer x)
    {
        Node_raw_pointer y = x->_left.get();
        x->_left = std::move(y->_right);
        y->_right = std::unique_ptr<Node_type>{x};
        y->_size = x->_size;
        x->_size = 1 + _size(x->_left.get()) + _size(x->_right.get());
        x->_height = 1 + std::max(_height(x->_left.get()), _height(x->_right.get()));
        y->_height = 1 + std::max(_height(y->_left.get()), _height(y->_right.get()));
        return y;
    }

    Node_raw_pointer _rotate_left(Node_raw_pointer x)
    {
        Node_raw_pointer y = x->_right.get();
        x->_left = std::move(y->_left);
        y->_left = std::unique_ptr<Node_type>{x};
        y->_size = x->_size;
        // TODO: change these into utility functions in the node class
        x->_size = 1 + _size(x->_left.get()) + _size(x->_right.get());
        x->_height = 1 + std::max(_height(x->_left.get()), _height(x->_right.get()));
        y->_height = 1 + std::max(_height(y->_left.get()), _height(y->_right.get()));
        return y;
    }

    Node_raw_pointer _delete(Node_raw_pointer x, Key_type key)
    {
        int cmp = Comparator_type()(key, x->_key);
        if (cmp < 0) {
            x->_left = _delete(x->_left.get(), key);
        } else if (cmp > 0) {
            x->_right = _delete(x->_right.get(), key);
        } else {
            if (x->_left == nullptr) {
                return x->_right.get();
            } else if (x->_right == nullptr) {
                return x->_left.get();
            } else {
                Node_raw_pointer y = x;
                x = _min(y->_right.get());
                x->_right = _delete_min(y->_right.get());
                x->_left = y->_left;
            }
        }
        x->_size = 1 + _size(x->_left.get()) + _size(x->_right.get());
        x->_height = 1 + std::max(_height(x->_left.get()), _height(x->_right.get()));
        return _balance(x);
    }

    Node_raw_pointer _delete_min(Node_raw_pointer x)
    {
        if (x->_left == nullptr) {
            return x->_right.get();
        }
        x->_left = _delete_min(x->_left.get());
        x->_size = 1 + _size(x->_left.get()) + _size(x->_right.get());
        x->_height = 1 + std::max(_height(x->_left.get()), _height(x->_right.get()));
        return _balance(x);
    }

    Node_raw_pointer _delete_max(Node_raw_pointer x)
    {
        if (x->_right == nullptr) {
            return x->_left.get();
        }
        x->_right = _delete_min(x->_right.get());
        x->_size = 1 + _size(x->_left.get()) + _size(x->_right.get());
        x->_height = 1 + std::max(_height(x->_left.get()), _height(x->_right.get()));
        return _balance(x);
    }

    Node_raw_pointer _min(Node_raw_pointer x) const
    {
        if (x->_left == nullptr) {
            return x;
        }
        return _min(x->_left.get());
    }

    Node_raw_pointer _max(Node_raw_pointer x) const
    {
        if (x->_right == nullptr) {
            return x;
        }
        return _max(x->_right.get());
    }

    Node_raw_pointer _floor(Node_raw_pointer x, Key_type key) const
    {
        if (x == nullptr) {
            return nullptr;
        }
        int cmp = Comparator_type()(key, x->_key);
        if (cmp == 0) {
            return x;
        }
        if (cmp < 0) {
            return _floor(x->_left.get(), key);
        }
        Node_raw_pointer y = _floor(x->_right.get(), key);
        if (y != nullptr) {
            return y;
        } else {
            return x;
        }
    }

    Node_raw_pointer _ceiling(Node_raw_pointer x, Key_type key) const
    {
        if (x == nullptr) {
            return nullptr;
        }
        int cmp = Comparator_type()(key, x->_key);
        if (cmp == 0) {
            return x;
        }
        if (cmp > 0) {
            return _ceiling(x->_right.get(), key);
        }
        Node_raw_pointer y = _ceiling(x->_left.get(), key);
        if (y != nullptr) {
            return y;
        } else {
            return x;
        }
    }

    Node_raw_pointer _select(Node_raw_pointer x, int k) const
    {
        if (x == nullptr) {
            return nullptr;
        }
        int t = _size(x->_left.get());
        if (t > k) {
            return _select(x->_left.get(), k);
        } else if (t < k) {
            return _select(x->_right.get(), k - t - 1);
        } else {
            return x;
        }
    }

    int _rank(Key_type key, Node_raw_pointer x) const
    {
        if (x == nullptr) {
            return 0;
        }
        int cmp = Comparator_type()(key, *(x->_key));
        if (cmp < 0) {
            return _rank(key, x->_left.get());
        } else if (cmp > 0) {
            return 1 + _size(x->_left.get()) + _rank(key, x->_right.get());
        } else {
            return _size(x->_left.get());
        }
    }

    void _keys_in_order(Node_raw_pointer x, Queue<Key_type>& queue) const
    {
        if (x == nullptr) {
            return;
        }
        _keys_in_order(x->_left.get(), queue);
        queue.enqueue(*(x->_key));
        _keys_in_order(x->_right.get(), queue);
    }

    void _keys(Node_raw_pointer x, Queue<Key_type> queue, Key_type lo, Key_type hi) const
    {
        if (x == nullptr) {
            return;
        }
        int cmplo = Comparator_type()(lo, x->_key);
        int cmphi = Comparator_type()(hi, x->_key);
        if (cmplo < 0) {
            _keys(x->_left.get(), queue, lo, hi);
        }
        if (cmplo <= 0 && cmphi >= 0) {
            queue.enqueue(x->_key);
        }
        if (cmphi > 0) {
            _keys(x->_right.get(), queue, lo, hi);
        }
    }

    bool _check() const
    {
        bool bst_check = _is_bst();
        bool avl_check = _is_avl();
        bool size_check = _is_size_consistent();
        bool rank_check = _is_rank_consistent();

        if (!bst_check) {
            Std_out::print_line("Binary_search_tree symmetric order is not consistent");
        }
        if (!avl_check) {
            Std_out::print_line("Binary_search_tree AVL property is not consistent");
        }
        if (!size_check) {
            Std_out::print_line("Binary_search_tree subtree size counts are not consistent");
        }
        if (!rank_check) {
            Std_out::print_line("Binary_search_tree ranks are not consistent");
        }

        return bst_check && avl_check && size_check && rank_check;
    }

    bool _is_bst() const { return _is_bst(_get_root(), min(), max()); }

    bool _is_bst(Node_raw_pointer x, Key_type min, Key_type max) const
    {
        if (x == nullptr) {
            return true;
        }
        if (Comparator_type()(*(x->_key), min) <= 0 && _size(x) != 1) {
            return false;
        }
        if (Comparator_type()(*(x->_key), min) >= 0 && _size(x) != 1) {
            return false;
        }
        return _is_bst(x->_left.get(), min, *(x->_key)) && _is_bst(x->_right.get(), *(x->_key), max);
    }

    bool _is_avl() const { return _is_avl(_get_root()); }

    bool _is_avl(Node_raw_pointer x) const
    {
        if (x == nullptr) {
            return true;
        }
        int bf = _balance_factor(x);
        if (bf > 1 || bf < -1) {
            return false;
        }
        return _is_avl(x->_left.get()) && _is_avl(x->_right.get());
    }

    bool _is_size_consistent() const { return _is_size_consistent(_get_root()); }

    bool _is_size_consistent(Node_raw_pointer x) const
    {
        if (x == nullptr) {
            return true;
        }
        if (x->_size != _size(x->_left.get()) + _size(x->_right.get()) + 1) {
            return false;
        }
        return _is_size_consistent(x->_left.get()) && _is_size_consistent(x->_right.get());
    }

    bool _is_rank_consistent() const
    {
        for (int i = 0; i < size(); ++i) {
            if (i != rank(*(select(i)))) {
                return false;
            }
        }
        for (auto key : keys()) {
            if (Comparator_type()(key, *(select(rank(key)))) != 0) {
                return false;
            }
        }
        return true;
    }
};


#endif //BINARY_SEARCH_TREE_H
