#ifndef RED_BLACK_BST_H
#define RED_BLACK_BST_H

#include <memory>
#include <cstddef>
#include <sstream>
#include <vector>
#include "utility.h"
#include "Std_out.h"

enum class Red_black_color : bool {
    red = true,
    black = false
};

Red_black_color _not(Red_black_color c);

template<typename Key, typename Value>
class Red_black_bst_node;

template<typename T>
struct Red_black_bst_key_comparator;

template<typename Key, typename Value, typename Comparator = Red_black_bst_key_comparator<Key>>
class Red_black_bst;

template<typename Key, typename Value>
struct Red_black_bst_node_pointer_traits {
    using Key_type = Key;
    using Value_type = Value;
    using Raw_key_pointer = Key*;
    using Raw_value_pointer = Value*;

    using Node_type = Red_black_bst_node<Key_type, Value_type>;
    using Raw_node_pointer = Red_black_bst_node<Key_type, Value_type>*;
    using Node_owning_pointer = Raw_node_pointer;
    //using Node_owning_pointer = std::unique_ptr<Node_type>;
    using Node_shared_pointer = std::shared_ptr<Node_type>;
    using Shared_value_pointer = std::shared_ptr<Value_type>;
    using Shared_key_pointer = std::shared_ptr<Key_type>;
    using Size_type = std::size_t;
};

template<typename Key, typename Value>
class Red_black_bst_node {
public:
    using Node_traits = Red_black_bst_node_pointer_traits<Key, Value>;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;
    using Raw_key_pointer = typename Node_traits::Raw_key_pointer;
    using Raw_value_pointer = typename Node_traits::Raw_value_pointer;
    using Node_type = typename Node_traits::Node_type;
    using Raw_node_pointer = typename Node_traits::Raw_node_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Node_shared_pointer = typename Node_traits::Node_shared_pointer;
    using Size_type = typename Node_traits::Size_type;

    Red_black_bst_node(Key_type& key, Value_type& val, Red_black_color color, int size)
            : _key{new Key{key}},
              _value{new Value{val}},
              _color{color},
              _size{size} {}

    Red_black_bst_node() : _key{nullptr}, _value{nullptr}, _color{Red_black_color::black}, _size{0} {}

    Red_black_bst_node(const Red_black_bst_node&) = default;

    Red_black_bst_node(Red_black_bst_node&&) = default;

    ~Red_black_bst_node()
    {
        if (_key != nullptr) {
            delete _key;
            _key = nullptr;
        }
        if (_value != nullptr) {
            delete _value;
            _value = nullptr;
        }
        if (_left != nullptr) {
            delete _left;
            _left = nullptr;
        }
        if (_right != nullptr) {
            delete _right;
            _right = nullptr;
        }
    };

    Red_black_bst_node& operator=(const Red_black_bst_node&) = default;

    Red_black_bst_node& operator=(Red_black_bst_node&&) = default;

private:
    Raw_key_pointer _key;
    Raw_value_pointer _value;

    Red_black_color _color; // of parent link
    int _size;

    Node_owning_pointer _left;
    Node_owning_pointer _right;

    template<typename, typename, typename>
    friend class Red_black_bst;
};

template<typename T>
struct Red_black_bst_key_comparator {
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
class Red_black_bst {
public:
    using Node_traits = Red_black_bst_node_pointer_traits<Key, Value>;
    using Node_type = typename Node_traits::Node_type;
    using Raw_node_pointer = typename Node_traits::Raw_node_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Node_shared_pointer = typename Node_traits::Node_shared_pointer;
    using Shared_value_pointer = typename Node_traits::Shared_value_pointer;
    using Shared_key_pointer = typename Node_traits::Shared_key_pointer;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;
    using Raw_value_pointer = typename Node_traits::Raw_value_pointer;
    using Raw_key_pointer = typename Node_traits::Raw_key_pointer;
    using Comparator_type = Comparator;

    using Reference_type = Value_type&;
    using Const_reference_type = const Value_type&;
    using Pointer_type = Value_type*;
    using Const_pointer_type = Value_type const*;
    using Size_type = std::size_t;
    using Difference_type = std::ptrdiff_t;

    Red_black_bst() = default;

    Red_black_bst(const Red_black_bst&) = default;

    Red_black_bst(Red_black_bst&&) = default;

    ~Red_black_bst() noexcept
    {
        _clear();
    }

    Red_black_bst& operator=(const Red_black_bst&) = default;

    Red_black_bst& operator=(Red_black_bst&&) = default;

    bool is_red(Raw_node_pointer n) const
    {
        if (n == nullptr) {
            return false;
        } else {
            return n->_color == Red_black_color::red;
        }
    }

    inline int size() const { return _size(_root); }

    inline bool is_empty() const { return _root == nullptr; }

    Raw_value_pointer get(Key_type& key) const
    {
        Raw_node_pointer n = _get(_root, key);
        if (n == nullptr) {
            return nullptr;
        }
        return n->_value;
    }

    inline bool contains(Key_type& key) const { return get(key) != nullptr; }

    void put(Key_type& key, Value_type& val)
    {
        _root = _put(_root, key, val);
        _root->_color = Red_black_color::black;
        // utility::alg_assert(_check(), "Red_black_bst invariant _check failed after \"put()\"");
    }

    void delete_min()
    {
        if (is_empty()) {
            throw utility::No_such_element_exception("The method \"delete_min()\" was called on an empty symbol table");
        }

        if (!is_red(_root->_left) && is_red(_root->_right)) {
            _root->_color = Red_black_color::red;
        }

        _root = _delete_min(_root);
        if (!is_empty()) {
            _root->_color = Red_black_color::black;
        }

        // utility::alg_assert(_check(), "Red_black_bst invariant _check failed after \"delete_min()\"");
    }

    void delete_max()
    {
        if (is_empty()) {
            throw utility::No_such_element_exception("The method \"delete_max()\" was called on an empty symbol table");
        }

        if (!is_red(_root->_left) && is_red(_root->_right)) {
            _root->_color = Red_black_color::red;
        }

        _root = _delete_max(_root);
        if (!is_empty()) {
            _root->_color = Red_black_color::black;
        }

        // utility::alg_assert(_check(), "Red_black_bst invariant _check failed after \"delete_max()\"");
    }

    void remove(Key_type& key)
    {
        if (!contains(key)) {
            return;
        }

        if (!is_red(_root->_left) && is_red(_root->_right)) {
            _root->_color = Red_black_color::red;
        }

        _root = _delete(_root, key);
        if (!is_empty()) {
            _root->_color = Red_black_color::black;
        }
    }

    Raw_key_pointer min() const
    {
        if (is_empty()) {
            throw utility::No_such_element_exception("The method \"min()\" was called on an empty symbol table");
        }
        return _min(_root)->_key;
    }

    Raw_key_pointer max() const
    {
        if (is_empty()) {
            throw utility::No_such_element_exception("The method \"max()\" was called on an empty symbol table");
        }
        return _max(_root)->_key;
    }

    Raw_key_pointer floor(Key_type& key) const
    {
        if (is_empty()) {
            throw utility::No_such_element_exception("The method \"floor()\" was called on an empty symbol table");
        }
        Raw_node_pointer x = _floor(_root, key);
        if (x == nullptr) {
            return nullptr;
        } else {
            return &(x->_key);
        }
    }

    Raw_key_pointer ceiling(Key_type& key) const
    {
        if (is_empty()) {
            throw utility::No_such_element_exception("The method \"ceiling()\" was called on an empty symbol table");
        }
        Raw_node_pointer x = _ceiling(_root, key);
        if (x == nullptr) {
            return nullptr;
        } else {
            return &(x->_key);
        }
    }

    Raw_key_pointer select(int k) const
    {
        if (k < 0 || k >= size()) {
            std::stringstream ss;
            ss << "The argument \"k\" is not _in the range 0-" << size() - 1;
            throw utility::Illegal_argument_exception(ss.str());
        }
        Raw_node_pointer x = _select(_root, k);
        if (x == nullptr) {
            return nullptr;
        } else {
            return x->_key;
        }
    }

    int rank(Key_type& key) const
    {
        return _rank(key, _root);
    }

    std::vector<Key_type> keys() const
    {
        if (is_empty()) {
            return {};
        }
        return keys(*min(), *max());
    }

    std::vector<Key_type> keys(Key_type& lo, Key_type& hi) const
    {
        std::vector<Key_type> kv;
        _keys(_root, kv, lo, hi);
        return kv;
    }

    int size(Key_type& lo, Key_type& hi) const
    {
        if (Comparator_type{}(lo, hi) > 0) {
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
    friend class Red_black_bst_iterator;

    template<typename, typename>
    friend class Red_black_bst_reverse_iterator;

    void _clear() noexcept
    {
        _clear(_root);
    }

    void _clear(Node_owning_pointer& node) noexcept
    {
        if (node != nullptr) {
            _clear(node->_left);
            _clear(node->_right);
            delete node;
            node = nullptr;
        }
    }

    int _size(Raw_node_pointer n) const
    {
        if (n == nullptr) {
            return 0;
        }
        return n->_size;
    }

    Raw_node_pointer _get(Raw_node_pointer n, Key_type& key) const
    {
        while (n != nullptr) {
            int cmp = Comparator_type{}(key, *(n->_key));
            if (cmp < 0) {
                n = n->_left;
            } else if (cmp > 0) {
                n = n->_right;
            } else {
                return n;
            }
        }
        return nullptr;
    }

    Raw_node_pointer _put(Raw_node_pointer n, Key_type& key, Value_type& val)
    {
        if (n == nullptr) {
            return new Red_black_bst_node<Key_type, Value_type>(key, val, Red_black_color::red, 1);
        }
        int cmp = Comparator_type()(key, *(n->_key));
        if (cmp < 0) {
            n->_left = _put(n->_left, key, val);
        } else if (cmp > 0) {
            n->_right = _put(n->_right, key, val);
        } else {
            n->_value = new Value{val};
            return n;
        }

        // fix right-leaning links
        if (is_red(n->_right) && !is_red(n->_left)) {
            n = _rotate_left(n);
        }
        if (is_red(n->_left) && (n->_left != nullptr && is_red(n->_left->_left))) {
            n = _rotate_right(n);
        }
        if (is_red(n->_left) && is_red(n->_right)) {
            _flip_colors(n);
        }

        n->_size = 1 + _size(n->_left) + _size(n->_right);
        return _balance(n);
    }

    Raw_node_pointer _balance(Raw_node_pointer n)
    {
        if (is_red(n->_right)) {
            n = _rotate_left(n);
        }
        if (is_red(n->_left) && is_red(n->_left->_left)) {
            n = _rotate_right(n);
        }
        if (is_red(n->_left) && is_red(n->_right)) { _flip_colors(n); }

        n->_size = 1 + _size(n->_left) + _size(n->_right);
        return n;
    }

    Raw_node_pointer _rotate_right(Raw_node_pointer n)
    {
        Raw_node_pointer x = n->_left;
        n->_left = x->_right;
        x->_right = n;
        x->_color = x->_right->_color;
        x->_right->_color = Red_black_color::red;
        x->_size = n->_size;
        n->_size = 1 + _size(n->_left) + _size(n->_right);
        return x;
    }

    Raw_node_pointer _rotate_left(Raw_node_pointer n)
    {
        Raw_node_pointer x = n->_right;
        n->_right = x->_left;
        x->_left = n;
        x->_color = x->_left->_color;
        x->_left->_color = Red_black_color::red;
        x->_size = n->_size;
        n->_size = 1 + _size(n->_left) + _size(n->_right);
        return x;
    }

    void _flip_colors(Raw_node_pointer n)
    {
        n->_color = _not(n->_color);
        n->_left->_color = _not(n->_left->_color);
        n->_right->_color = _not(n->_right->_color);
    }

    Raw_node_pointer _move_red_left(Raw_node_pointer n)
    {
        _flip_colors(n);
        if (is_red(n->_right->_left)) {
            n->_right = _rotate_right(n->_right);
            n = _rotate_left(n);
            _flip_colors(n);
        }
        return n;
    }

    Raw_node_pointer _move_red_right(Raw_node_pointer n)
    {
        _flip_colors(n);
        if (is_red(n->_left->_left)) {
            n = _rotate_right(n);
            _flip_colors(n);
        }
        return n;
    }

    Raw_node_pointer _delete(Raw_node_pointer n, Key_type& key)
    {
        Comparator_type comp{};
        if (comp(key, *(n->_key)) < 0) {
            if (!is_red(n->_left) && !is_red(n->_left->_left)) {
                n = _move_red_left(n);
            }
            n->_left = _delete(n->_left, key);
        } else {
            if (is_red(n->_left)) {
                n = _rotate_right(n);
            }
            if (comp(key, *(n->_key)) == 0 && (n->_right == nullptr)) {
                return nullptr;
            }
            if (!is_red(n->_right) && !is_red(n->_right->_left)) {
                n = _move_red_right(n);
            }
            if (comp(key, *(n->_key)) == 0) {
                Raw_node_pointer x = _min(n->_right);
                n->_key = x->_key;
                n->_value = x->_value;
                n->_right = _delete_min(n->_right);
            } else {
                n->_right = _delete(n->_right, key);
            }
        }
        return _balance(n);
    }

    Raw_node_pointer _delete_min(Raw_node_pointer n)
    {
        if (n->_left == nullptr) {
            return nullptr;
        }

        if (!is_red(_root->_left) && !is_red(_root->_right)) {
            n = _move_red_left(n);
        }

        n->_left = _delete_min(n->_left);
        return _balance(n);
    }

    Raw_node_pointer _delete_max(Raw_node_pointer n)
    {
        if (is_red(n->_left)) {
            n = _rotate_right(n);
        }

        if (n->_right == nullptr) {
            return nullptr;
        }

        if (!is_red(_root->_right) && is_red(_root->_right->_left)) {
            n = _move_red_left(n);
        }

        n->_right = _delete_max(n->_right);
        return _balance(n);
    }

    Raw_node_pointer _min(Raw_node_pointer n) const
    {
        if (n->_left == nullptr) {
            return n;
        }
        return _min(n->_left);
    }

    Raw_node_pointer _max(Raw_node_pointer n) const
    {
        if (n->_right == nullptr) {
            return n;
        }
        return _max(n->_right);
    }

    Raw_node_pointer _floor(Raw_node_pointer n, Key_type& key) const
    {
        if (n == nullptr) {
            return nullptr;
        }
        int cmp = Comparator_type{}(key, *(n->_key));
        if (cmp == 0) {
            return n;
        }
        if (cmp < 0) {
            return _floor(n->_left, key);
        }
        Raw_node_pointer y = _floor(n->_right, key);
        if (y != nullptr) {
            return y;
        } else {
            return n;
        }
    }

    Raw_node_pointer _ceiling(Raw_node_pointer x, Key_type& key) const
    {
        if (x == nullptr) {
            return nullptr;
        }
        int cmp = Comparator_type{}(key, x->_key);
        if (cmp == 0) {
            return x;
        }
        if (cmp > 0) {
            return _ceiling(x->_right, key);
        }
        Raw_node_pointer y = _ceiling(x->_left, key);
        if (y != nullptr) {
            return y;
        } else {
            return x;
        }
    }

    Raw_node_pointer _select(Raw_node_pointer x, int k) const
    {
        if (x == nullptr) {
            return nullptr;
        }
        int t = _size(x->_left);
        if (t > k) {
            return _select(x->_left, k);
        } else if (t < k) {
            return _select(x->_right, k - t - 1);
        } else {
            return x;
        }
    }

    int _rank(Key_type& key, Raw_node_pointer x) const
    {
        if (x == nullptr) {
            return 0;
        }
        int cmp = Comparator_type{}(key, *(x->_key));
        if (cmp < 0) {
            return _rank(key, x->_left);
        } else if (cmp > 0) {
            return 1 + _size(x->_left) + _rank(key, x->_right);
        } else {
            return _size(x->_left);
        }
    }

    void _keys(Raw_node_pointer x, std::vector<Key_type>& keys, Key_type lo, Key_type hi) const
    {
        if (x == nullptr) {
            return;
        }
        Comparator_type comp{};
        int cmplo = comp(lo, *(x->_key));
        int cmphi = comp(hi, *(x->_key));
        if (cmplo < 0) {
            _keys(x->_left, keys, lo, hi);
        }
        if (cmplo <= 0 && cmphi >= 0) {
            keys.emplace_back(*(x->_key));
        }
        if (cmphi > 0) {
            _keys(x->_right, keys, lo, hi);
        }
    }

    bool _check() const
    {
        bool bst_check = _is_bst();
        bool size_check = _is_size_consistent();
        bool rank_check = _is_rank_consistent();
        bool two_three_check = _is_two_three();
        bool balance_check = _is_balanced();

        if (!bst_check) {
            Std_out::print_line("Red_black_bst symmetric _order is not consistent");
        }
        if (!size_check) {
            Std_out::print_line("Red_black_bst subtree size counts are not consistent");
        }
        if (!rank_check) {
            Std_out::print_line("Red_black_bst ranks are not consistent");
        }
        if (!two_three_check) {
            Std_out::print_line("Red_black_bst is not a 2-3 tree");
        }
        if (!balance_check) {
            Std_out::print_line("Red_black_bst is not balanced");
        }

        return bst_check && size_check && rank_check && two_three_check && balance_check;
    }

    // TODO: _check if this achieves the correct result, handle nullptr
    inline bool _is_bst() const { return _is_bst(_root, *min(), *max()); }

    bool _is_bst(Raw_node_pointer n, Key_type& min, Key_type& max) const
    {
        if (n == nullptr) {
            return true;
        }
        Comparator_type comp{};
        if (comp(*(n->_key), min) <= 0) {
            return false;
        }
        if (comp(*(n->_key), min) >= 0) {
            return false;
        }
        return _is_bst(n->_left, min, *(n->_key)) && _is_bst(n->_right, *(n->_key), max);
    }

    inline bool _is_size_consistent() const { return _is_size_consistent(_root); }

    bool _is_size_consistent(Raw_node_pointer n) const
    {
        if (n == nullptr) {
            return true;
        }
        if (n->_size != _size(n->_left) + _size(n->_right) + 1) {
            return false;
        }
        return _is_size_consistent(n->_left) && _is_size_consistent(n->_right);
    }

    bool _is_rank_consistent() const
    {
        for (auto i = 0; i < size(); ++i) {
            if (i != rank(*(select(i)))) {
                return false;
            }
        }
        for (auto key : keys()) {
            if (Comparator_type()(key, *(select(rank(*key)))) != 0) {
                return false;
            }
        }
        return true;
    }

    inline bool _is_two_three() const { return _is_two_three(_root); }

    bool _is_two_three(Raw_node_pointer n) const
    {
        if (n == nullptr) {
            return true;
        }
        if (is_red(n->_right)) {
            return false;
        }
        if (n != _root && is_red(n) && is_red(n->_left)) {
            return false;
        }
        return _is_two_three(n->_left) && _is_two_three(n->_right);
    }

    bool _is_balanced() const
    {
        auto black = 0;
        Raw_node_pointer n = _root;
        while (n != nullptr) {
            if (!is_red(n)) {
                ++black;
            }
            n = n->_left;
        }
        return _is_balanced(_root, black);
    }

    bool _is_balanced(Raw_node_pointer n, int black) const
    {
        if (n == nullptr) {
            return black == 0;
        }
        if (!is_red(n)) {
            --black;
        }
        return _is_balanced(n->_left, black) && _is_balanced(n->_right, black);
    }
};

#endif // RED_BLACK_BST_H
