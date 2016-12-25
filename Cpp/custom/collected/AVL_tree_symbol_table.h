#ifndef COLLECTED_AVL_TREE_SYMBOL_TABLE_H
#define COLLECTED_AVL_TREE_SYMBOL_TABLE_H

#include<cstddef>

#include"utility.h"

template<typename Key_type, typename Value_type>
class AVL_tree_symbol_table;

template<class _Tp, class _NodePtr, class _DiffType>
class AVL_tree_iterator;

template<class _Tp, class _ConstNodePtr, class _DiffType>
class AVL_tree_const_iterator;

template<typename Key_type, typename Value_type>
class AVL_tree_node;

template<typename Key_type, typename Value_type>
struct AVL_tree_node_pointer_traits {
    using key_type = Key_type;
    using value_type = Value_type;
    using node = AVL_tree_node<Key_type, Value_type>
    using node_pointer = node *;
    using link_pointer = node_pointer;
    using size_type = std::size_t;
};

template<typename Key_type, typename Value_type>
class AVL_tree_node {
public:
    using Node_traits = AVL_tree_node_pointer_traits<Key_type, Value_type>;
    using key_type = typename Node_traits::key_type;
    using value_type = typename Node_traits::value_type;
    using node_pointer = typename Node_traits::node_pointer;
    using link_pointer = typename Node_traits::link_pointer;
    using size_type = typename Node_traits::size_type;

private:
    key_type key_;
    value_type value_;

    size_type height_;
    size_type size_;

    node_pointer left_;
    node_pointer right_;

    ~AVL_tree_node() = delete;

    AVL_tree_node(AVL_tree_node const &) = delete;

    AVL_tree_node &operator=(AVL_tree_node const &) = delete;

    template<typename, typename>
    friend class AVL_tree_symbol_table;

    template<typename, typename>
    friend class AVL_tree_iterator;

    template<typename, typename>
    friend class AVL_tree_const_iterator;

public:
    AVL_tree_node(key_type &key, value_type &val, int height, int size) : key_{key}, value_{val}, size_{static_cast<size_type>(size)}, height_{static_cast<size_type>(height)} {}
};

// TODO: add default Compare
template<typename Key_type, typename Value_type, typename Comparator = std::less>
class AVL_tree_symbol_table {
private:
    using Node_traits = AVL_tree_node_pointer_traits<Key_type, Value_type>;

    using node = typename Node_traits::node;
    using node_pointer = typename Node_traits::node_pointer;
    using node_const_pointer = typename Node_traits::node_pointer;
    using link_pointer = typename Node_traits::link_pointer;
    using link_const_pointer = link_pointer;

    node_pointer root_;

public:
    using value_type = typename Node_traits::value_type;
    using key_type = typename Node_traits::key_type;
    using key_comparator = Comparator;

    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = value_type const *;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;  // check on this because of the relationship with max_size
    using iterator = AVL_tree_iterator<value_type, key_type>;

//    typedef typename __alloc_traits::pointer pointer;
//    typedef typename __alloc_traits::const_pointer const_pointer;
//    typedef typename __alloc_traits::size_type size_type;
//    typedef typename __alloc_traits::difference_type difference_type;
//
//public:
//    typedef typename _NodeTypes::__void_pointer __void_pointer;
//
//    typedef typename _NodeTypes::__node_type __node;
//    typedef typename _NodeTypes::__node_pointer __node_pointer;
//
//    typedef typename _NodeTypes::__node_base_type __node_base;
//    typedef typename _NodeTypes::__node_base_pointer __node_base_pointer;
//
//    typedef typename _NodeTypes::__end_node_type __end_node_t;
//    typedef typename _NodeTypes::__end_node_pointer __end_node_ptr;
//
//    typedef typename _NodeTypes::__parent_pointer __parent_pointer;
//    typedef typename _NodeTypes::__iter_pointer __iter_pointer;
//
//    typedef typename __rebind_alloc_helper<__alloc_traits, __node>::type __node_allocator;
//    typedef allocator_traits<__node_allocator> __node_traits;
//
    inline bool is_empty() { return root_ == nullptr; }

    size_type size() { return size(root_); }

    size_type size(node_pointer n) {
        if (n == nullptr) {
            return 0;
        }
        return n->size_;
    }

    size_type height() { return height(root_); }

    size_type height(node_pointer n) {
        if (n == nullptr) {
            return 0;
        }
        return n->height_;
    }

    value_type *get(key_type &key) { // TODO: how to handle return type
        node_pointer n = get(root_, key);
        if (n == nullptr) {
            return nullptr;
        }
        return &(n->value_);
    }

    node_pointer get(node_pointer n, key_type &key) {
        if (n == nullptr) {
            return nullptr;
        }
        if (key_comparator()(key, n->key_)) {
            return get(n->left_, key);
        } else if (key_comparator()(n->key_, key)) {
            return get(n->right_, key);
        } else {
            return n;
        }
    }

    bool contains(key_type &key) { return get(key) != nullptr; }

    void put(key_type &key, value_type &val) {
        root_ = put(root_, key, val);
        utility::assert(_check(), "AVL_tree_symbol_table invariant check failed after put()")
    }

private:
    bool _check() {
        bool bst_check = _is_bst();
        bool avl_check = _is_avl();
        bool size_check = _is_size_consistent();
        bool rank_check = _is_rank_consistent();

        if (!bst_check) {
            std::cerr << "AVL_tree_symbol_table symmetric order is not consistent\n";
        }
        if (!avl_check) {
            std::cerr << "AVL_tree_symbol_table AVL property is not consistent\n";
        }
        if (!size_check) {
            std::cerr << "AVL_tree_symbol_table subtree size counts are not consistent\n";
        }
        if (!rank_check) {
            std::cerr << "AVL_tree_symbol_table ranks are not consistent\n";
        }

        return bst_check && avl_check && size_check && rank_check;
    }

    // TODO: fix this up
    bool _is_bst() { return _is_bst(root_); }

    bool _is_bst(node_pointer n, value_type min, value_type max) {
        if (n == nullptr) {
            return true;
        }
        if (min != nullptr && key_comparator()(n->key_, min)) {
            return false;
        }
        if (max != nullptr && key_comparator()(n->key_, min)) {
            return false;
        }
        return _is_bst(n->left_, min, n->key_) && _is_bst(n->right_, n->key_, max);
    }

//    template<class _Tp, class _Compare, class _Allocator>
//    template<class _Key>
//    typename __tree<_Tp, _Compare, _Allocator>::iterator
//    __tree<_Tp, _Compare, _Allocator>::find(const _Key &__v) {
//        iterator __p = __lower_bound(__v, __root(), __end_node());
//        if (__p != end() && !value_comp()(__v, *__p)) {
//            return __p;
//        }
//        return end();
//    }
//
//
//    bool empty() const;
//    size_type size() const;
//    const_iterator begin() const;
//    const_iterator end() const;
//    const_reverse_iterator rbegin() const;
//    const_reverse_iterator rend() const;
//    const_reference front() const;
//    const_reference back() const;
//    const_iterator find(const key_type& searchKey) const;
//    key_compare key_comp() const;
//    const Node* root() const;
//    const Node* head() const;
//    const Node* tail() const;
//
//    iterator begin();
//    iterator end();
//    reverse_iterator rbegin();
//    reverse_iterator rend();
//    reference front();
//    reference back();
//    AvlTree& operator=(const AvlTree& rhs);
//    iterator find(const key_type& searchKey);
//    void clear();
//
//private:
//    Node* _copyNode(Node* sourceNode, Node* newParent);
//    Node* _createNode(const value_type& sourceElement);
//    void _destroyNode(Node* n);
//    void _destroyAllNodes();
//    void _overwriteElement(Node* n, const value_type& sourceElement);
//
//    typedef Key key_type;
//    typedef Mapped mapped_type;
//    typedef Pair<const key_type, mapped_type> value_type;
//    typedef Predicate key_compare;
//    typedef int difference_type;
//    typedef unsigned int size_type;
//    typedef ConstIter<AvlTree> const_iterator;
//    typedef ReverseIter<const_iterator> const_reverse_iterator;
//    typedef const value_type* const_pointer;
//    typedef const value_type& const_reference;
//    typedef BinaryTreeIter<AvlTree> iterator;
//    typedef ReverseIter<iterator> reverse_iterator;
//    typedef value_type* pointer;
//    typedef value_type& reference;
//    typedef AvlTreeNode<key_type, mapped_type> Node;
};

#endif //COLLECTED_AVL_TREE_SYMBOL_TABLE_H
