#ifndef AVL_TREE_SYMBOL_TABLE_H
#define AVL_TREE_SYMBOL_TABLE_H

#include <algorithm>
#include <cstddef>
#include <memory>

#include "Queue.h"
#include "Std_out.h"
#include "utility.h"

// NOTE: removed iterators because they require parent node links

template<typename Key_t, typename Value_t>
class AVL_tree_node;

template<typename Key_t, typename Value_t, typename Comparator_t = std::less<Key_t>>
class AVL_tree_symbol_table;

template<typename Key_t, typename Value_t>
struct AVL_tree_node_pointer_traits {
    using Key_type = Key_t;
    using Value_type = Value_t;
    using Node_type = AVL_tree_node<Key_type, Value_type>;
    using Unowned_node_ptr = Node_type *;
    using Owning_node_ptr = std::unique_ptr<Node_type>;
};

// remove use of shared_ptr for keys and values to make implementation
// more lightweight
template<typename Key_t, typename Value_t>
class AVL_tree_node {
public:
    using Node_traits = AVL_tree_node_pointer_traits<Key_t, Value_t>;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;
    using Node_type = typename Node_traits::Node_type;
    using Unowned_node_ptr = typename Node_traits::Unowned_node_ptr;
    using Owning_node_ptr = typename Node_traits::Owning_node_ptr;

    AVL_tree_node(Key_type const &key, Value_type const &val, int height, int size)
            : _key{key},
              _value{val},
              _height{height},
              _size{size},
              _left{nullptr},
              _right{nullptr} {}

    AVL_tree_node(AVL_tree_node &&rhs) noexcept
            : _key{rhs._key},
              _value{rhs._value},
              _height{rhs._height},
              _size{rhs._size},
              _left{std::move(rhs._left)},
              _right{std::move(rhs._right)} {}

    ~AVL_tree_node() = default;

    AVL_tree_node &operator=(AVL_tree_node &&rhs) noexcept
    {
        _key = rhs._key;
        _value = rhs._value;
        _height = rhs._height;
        _size = rhs._size;
        _left = std::move(rhs._left);
        _right = std::move(rhs._right);
        return *this;
    }

private:
    Key_type _key;
    Value_type _value;

    int _height;
    int _size;

    Owning_node_ptr _left;
    Owning_node_ptr _right;

    template<typename, typename, typename>
    friend
    class AVL_tree_symbol_table;
};

template<typename Key_t, typename Value_t, typename Comparator_t>
class AVL_tree_symbol_table {
public:
    using Node_traits = AVL_tree_node_pointer_traits<Key_t, Value_t>;
    using Node_type = typename Node_traits::Node_type;
    using Unowned_node_ptr = typename Node_traits::Unowned_node_ptr;
    using Owning_node_ptr = typename Node_traits::Owning_node_ptr;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;

    AVL_tree_symbol_table() : _root{nullptr} {}

    AVL_tree_symbol_table(AVL_tree_symbol_table &&rhs) noexcept : _root{std::move(rhs._root)} {}

    ~AVL_tree_symbol_table() = default;

    AVL_tree_symbol_table &operator=(AVL_tree_symbol_table &&rhs) noexcept
    {
        _root = std::move(rhs._root);
        return *this;
    }

    bool is_empty() const noexcept
    {
        return _root == nullptr;
    }

    int size() const
    {
        return _size(_get_root());
    }

    int height() const
    {
        return _height(_get_root());
    }

    Value_type get(Key_type const &key) const
    {
        auto n = _get(_get_root(), key);
        if (n == nullptr) {
            throw utility::No_such_element_exception{
                    "The method \"get()\" was called with a key value that is not in the symbol table"
            };
        }
        return n->_value;
    }

    bool contains(Key_type const &key) const
    {
        try {
            get(key);
            return true;
        }
        catch (utility::No_such_element_exception &) {
            return false;
        }
    }

    void put(Key_type const &key, Value_type const &val)
    {
        _update_root(_put(_get_root(), key, val));
#ifndef NDEBUG
        auto b = _check();
        utility::alg_assert(b, "AVL_tree_symbol_table invariant check failed after \"put()\"");
#endif
    }

    void delete_min()
    {
        if (is_empty()) {
            throw utility::No_such_element_exception{"The method \"delete_min()\" was called on an empty symbol table"};
        }
        _update_root(_delete_min(_get_root()));
#ifndef NDEBUG
        utility::alg_assert(_check(), "AVL_tree_symbol_table invariant check failed after \"delete_min()\"");
#endif
    }

    void delete_max()
    {
        if (is_empty()) {
            throw utility::No_such_element_exception{"The method \"delete_max()\" was called on an empty symbol table"};
        }
        _update_root(_delete_max(_get_root()));
#ifndef NDEBUG
        utility::alg_assert(_check(), "AVL_tree_symbol_table invariant check failed after \"delete_max()\"");
#endif
    }

    Key_type min() const
    {
        if (is_empty()) {
            throw utility::No_such_element_exception{"The method \"min()\" was called on an empty symbol table"};
        }
        return _min(_get_root())->_key;
    }

    Key_type max() const
    {
        if (is_empty()) {
            throw utility::No_such_element_exception{"The method \"max()\" was called on an empty symbol table"};
        }
        return _max(_get_root())->_key;
    }

    Key_type floor(Key_type const &key) const
    {
        if (is_empty()) {
            throw utility::No_such_element_exception{"The method \"floor()\" was called on an empty symbol table"};
        }
        auto x = _floor(_get_root(), key);
        if (x == nullptr) {
            throw utility::Illegal_argument_exception{"The input key value does not have a floor"};
        }
        return x->_key;
    }

    Key_type ceiling(Key_type &key) const
    {
        if (is_empty()) {
            throw utility::No_such_element_exception{"The method \"ceiling()\" was called on an empty symbol table"};
        }
        auto x = _ceiling(_get_root(), key);
        if (x == nullptr) {
            throw utility::Illegal_argument_exception{"The input key value does not have a ceiling"};
        }
        return x->_key;
    }

    Key_type select(int k) const
    {
        if (k < 0 || k >= size()) {
            throw utility::Illegal_argument_exception{
                    "The argument is not in the range 0-" + std::to_string(size() - 1)
            };
        }
        auto x = _select(_get_root(), k);
        return x->_key;
    }

    int rank(Key_type const &key) const
    {
        return _rank(key, _get_root());
    }

    Queue<Key_type> keys() const
    {
        return keys_in_order();
    }

    Queue<Key_type> keys_in_order() const
    {
        auto queue = Queue<Key_type>{};
        _keys_in_order(_get_root(), queue);
        return queue;
    }

    Queue<Key_type> keys_in_level_order() const
    {
        auto queue = Queue<Key_type>{};
        if (!is_empty()) {
            auto queue2 = Queue<Unowned_node_ptr>{};
            auto root = _get_root();
            queue2.enqueue(root);
            while (!queue2.is_empty()) {
                auto x = queue2.dequeue();
                auto n = x->_key;
                queue.enqueue(n);
                if (x->_left != nullptr) {
                    auto l = x->_left.get();
                    queue2.enqueue(l);
                }
                if (x->_right != nullptr) {
                    auto r = x->_right.get();
                    queue2.enqueue(r);
                }
            }
        }
        return queue;
    }

    Queue<Key_type> keys(Key_type &lo, Key_type &hi) const
    {
        auto queue = Queue<Key_type>{};
        _keys(_get_root(), queue, lo, hi);
        return queue;
    }

    int size(Key_type const &lo, Key_type const &hi) const
    {
        if (Comparator_t{}(lo, hi) > 0) {
            return 0;
        }
        if (contains(hi)) {
            return rank(hi) - rank(lo) + 1;
        }
        return rank(hi) - rank(lo);
    }

private:
    Owning_node_ptr _root;

    Unowned_node_ptr _get_root() const
    {
        return _root.get();
    }

    void _update_root(Unowned_node_ptr new_root)
    {
        if (new_root != _get_root()) {
            _root = Owning_node_ptr{new_root};
        }
    }

    int _size(Unowned_node_ptr n) const
    {
        if (n == nullptr) {
            return 0;
        }
        return n->_size;
    }

    int _height(Unowned_node_ptr n) const
    {
        if (n == nullptr) {
            return 0;
        }
        return n->_height;
    }

    Unowned_node_ptr _get(Unowned_node_ptr n, Key_type const &key) const
    {
        if (n == nullptr) {
            return nullptr;
        }
        auto comp = Comparator_t{};
        if (comp(key, n->_key)) {
            return _get(n->_left.get(), key);
        }
        if (comp(n->_key, key)) {
            return _get(n->_right.get(), key);
        }
        return n;
    }

    // possibly reseats _left and _right
    Unowned_node_ptr _put(Unowned_node_ptr x, Key_type const &key, Value_type const &val)
    {
        if (x == nullptr) {
            return new AVL_tree_node<Key_type, Value_type>(key, val, 0, 1);
        }
        auto comp = Comparator_t{};
        if (comp(key, x->_key)) {
            x->_left = Owning_node_ptr{_put(x->_left.get(), key, val)};
        } else if (comp(x->_key, key)) {
            x->_right = Owning_node_ptr{_put(x->_right.get(), key, val)};
        } else {
            x->_value = val;
            return x;
        }
        x->_size = 1 + _size(x->_left.get()) + _size(x->_right.get());
        x->_height = 1 + std::max(_height(x->_left.get()), _height(x->_right.get()));
        return _balance(x);
    }

    // possibly reseats _left and _right
    Unowned_node_ptr _balance(Unowned_node_ptr x)
    {
        if (_balance_factor(x) < -1) {
            if (_balance_factor(x->_right.get()) > 0) {
                x->_right = Owning_node_ptr{_rotate_right(x->_right.get())};
            }
            x = _rotate_left(x);
        } else if (_balance_factor(x) > 1) {
            if (_balance_factor(x->_left.get()) < 0) {
                x->_left = Owning_node_ptr{_rotate_left(x->_left.get())};
            }
            x = _rotate_right(x);
        }
        return x;
    }

    int _balance_factor(Unowned_node_ptr x) const
    {
        return _height(x->_left.get()) - _height(x->_right.get());
    }

    // possibly reseats _left and _right
    Unowned_node_ptr _rotate_right(Unowned_node_ptr x)
    {
        auto y = x->_left.get();
        x->_left = std::move(y->_right);
        y->_right = Owning_node_ptr{x};
        y->_size = x->_size;
        x->_size = 1 + _size(x->_left.get()) + _size(x->_right.get());
        x->_height = 1 + std::max(_height(x->_left.get()), _height(x->_right.get()));
        y->_height = 1 + std::max(_height(y->_left.get()), _height(y->_right.get()));
        return y;
    }

    // possibly reseats _left and _right
    Unowned_node_ptr _rotate_left(Unowned_node_ptr x)
    {
        auto y = x->_right.get();
        x->_left = std::move(y->_left);
        y->_left = Owning_node_ptr{x};
        y->_size = x->_size;
        x->_size = 1 + _size(x->_left.get()) + _size(x->_right.get());
        x->_height = 1 + std::max(_height(x->_left.get()), _height(x->_right.get()));
        y->_height = 1 + std::max(_height(y->_left.get()), _height(y->_right.get()));
        return y;
    }

    // possibly reseats _left and _right
    Unowned_node_ptr _delete(Unowned_node_ptr x, Key_type &key)
    {
        auto comp = Comparator_t{};
        if (comp(key, x->_key)) {
            x->_left = _delete(x->_left.get(), key);
        } else if (comp(x->_key, key)) {
            x->_right = _delete(x->_right.get(), key);
        } else {
            if (x->_left == nullptr) {
                return x->_right.get();
            }
            if (x->_right == nullptr) {
                return x->_left.get();
            }
            auto y = x;
            x = _min(y->_right.get());
            x->_right = _delete_min(y->_right.get());
            x->_left = y->_left;
        }
        x->_size = 1 + _size(x->_left.get()) + _size(x->_right.get());
        x->_height = 1 + std::max(_height(x->_left.get()), _height(x->_right.get()));
        return _balance(x);
    }

    // possibly reseats _left
    Unowned_node_ptr _delete_min(Unowned_node_ptr x)
    {
        if (x->_left == nullptr) {
            return x->_right.get();
        }
        x->_left = _delete_min(x->_left.get());
        x->_size = 1 + _size(x->_left.get()) + _size(x->_right.get());
        x->_height = 1 + std::max(_height(x->_left.get()), _height(x->_right.get()));
        return _balance(x);
    }

    // possibly reseats _right
    Unowned_node_ptr _delete_max(Unowned_node_ptr x)
    {
        if (x->_right == nullptr) {
            return x->_left.get();
        }
        x->_right = _delete_min(x->_right.get());
        x->_size = 1 + _size(x->_left.get()) + _size(x->_right.get());
        x->_height = 1 + std::max(_height(x->_left.get()), _height(x->_right.get()));
        return _balance(x);
    }

    Unowned_node_ptr _min(Unowned_node_ptr x) const
    {
        if (x->_left == nullptr) {
            return x;
        }
        return _min(x->_left.get());
    }

    Unowned_node_ptr _max(Unowned_node_ptr x) const
    {
        if (x->_right == nullptr) {
            return x;
        }
        return _max(x->_right.get());
    }

    Unowned_node_ptr _floor(Unowned_node_ptr x, Key_type &key) const
    {
        if (x == nullptr) {
            return nullptr;
        }
        auto comp = Comparator_t{};
        if (!comp(key, x->_key) && !comp(x->_key, key)) {
            return x;
        }
        if (comp(key, x->_key)) {
            return _floor(x->_left.get(), key);
        }
        auto y = _floor(x->_right.get(), key);
        if (y != nullptr) {
            return y;
        }
        return x;
    }

    Unowned_node_ptr _ceiling(Unowned_node_ptr x, Key_type &key) const
    {
        if (x == nullptr) {
            return nullptr;
        }
        auto comp = Comparator_t{};
        if (!comp(key, x->_key) && !comp(x->_key, key)) {
            return x;
        }
        if (comp(key, x->_key)) {
            return _ceiling(x->_right.get(), key);
        }
        auto y = _ceiling(x->_left.get(), key);
        if (y != nullptr) {
            return y;
        }
        return x;
    }

    // basic test leads to condition where size of node is 2 but both left and right are null
    Unowned_node_ptr _select(Unowned_node_ptr x, int k) const
    {
        if (x == nullptr) {
            return nullptr;
        }
        auto t = _size(x->_left.get());
        if (k < t) {
            return _select(x->_left.get(), k);
        }
        if (t < k) {
            return _select(x->_right.get(), k - t - 1);
        }
        return x;
    }

    int _rank(Key_type const &key, Unowned_node_ptr x) const
    {
        if (x == nullptr) {
            return 0;
        }
        auto comp = Comparator_t{};
        if (comp(key, x->_key)) {
            return _rank(key, x->_left.get());
        }
        if (comp(x->_key, key)) {
            return 1 + _size(x->_left.get()) + _rank(key, x->_right.get());
        }
        return _size(x->_left.get());
    }

    void _keys_in_order(Unowned_node_ptr x, Queue<Key_type> &queue) const
    {
        if (x == nullptr) {
            return;
        }
        _keys_in_order(x->_left.get(), queue);
        auto n = x->_key;
        queue.enqueue(n);
        _keys_in_order(x->_right.get(), queue);
    }

    void _keys(Unowned_node_ptr x, Queue<Key_type> queue, Key_type lo, Key_type hi) const
    {
        if (x == nullptr) {
            return;
        }
        auto comp = Comparator_t{};
        if (comp(lo, x->_key)) {
            _keys(x->_left.get(), queue, lo, hi);
        }
        if (!comp(x->_key, lo) && !comp(hi, x->_key)) {
            auto n = x->_key;
            queue.enqueue(n);
        }
        if (comp(x->_key, hi)) {
            _keys(x->_right.get(), queue, lo, hi);
        }
    }

    bool _check() const
    {
        auto bst_check = _is_bst();
        auto avl_check = _is_avl();
        auto size_check = _is_size_consistent();
        auto rank_check = _is_rank_consistent();

        if (!bst_check) {
            Std_out::print(stderr, "AVL_tree_symbol_table symmetric order is not consistent");
        }
        if (!avl_check) {
            Std_out::print(stderr, "AVL_tree_symbol_table AVL property is not consistent");
        }
        if (!size_check) {
            Std_out::print(stderr, "AVL_tree_symbol_table subtree size counts are not consistent");
        }
        if (!rank_check) {
            Std_out::print(stderr, "AVL_tree_symbol_table ranks are not consistent");
        }

        return bst_check && avl_check && size_check && rank_check;
    }

    bool _is_bst() const
    {
        return _is_bst(_get_root(), nullptr, nullptr);
    }

    bool _is_bst(Unowned_node_ptr x, Key_type *min, Key_type *max) const
    {
        if (x == nullptr) {
            return true;
        }
        auto comp = Comparator_t{};
        if (min != nullptr && !comp(*min, x->_key)) {
            return false;
        }
        if (max != nullptr && !comp(x->_key, *max)) {
            return false;
        }
        return _is_bst(x->_left.get(), min, &x->_key) && _is_bst(x->_right.get(), &x->_key, max);
    }

    bool _is_avl() const
    {
        return _is_avl(_get_root());
    }

    bool _is_avl(Unowned_node_ptr x) const
    {
        if (x == nullptr) {
            return true;
        }
        auto bf = _balance_factor(x);
        if (bf > 1 || bf < -1) {
            return false;
        }
        return _is_avl(x->_left.get()) && _is_avl(x->_right.get());
    }

    bool _is_size_consistent() const { return _is_size_consistent(_get_root()); }

    bool _is_size_consistent(Unowned_node_ptr x) const
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
        auto sz = size();
        for (auto i = 0; i < sz; ++i) {
            // TODO: this now throws
            auto k = select(i);
            if (i != rank(k)) {
                return false;
            }
        }
        auto comp = Comparator_t{};
        for (const auto key : keys()) {
            // TODO: this now throws
            auto r = rank(key);
            if (comp(key, select(r)) != 0) {
                return false;
            }
        }
        return true;
    }
};

#endif // AVL_TREE_SYMBOL_TABLE_H
