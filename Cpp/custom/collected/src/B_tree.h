#ifndef B_TREE_H
#define B_TREE_H

#include <memory>
#include <vector>
#include <sstream>

const static int _max_num_children = 4;

template<typename Key, typename Value>
class B_tree_node;

template<typename Key, typename Value>
class B_tree_entry;

template<typename T>
struct B_tree_key_comparator;

template<typename Key, typename Value, typename Comparator = B_tree_key_comparator<Key>>
class B_tree;

template<typename Key, typename Value>
struct B_tree_node_pointer_traits {
    using Key_type = Key;
    using Value_type = Value;
    using Raw_key_pointer = Key*;
    using Raw_value_pointer = Value*;

    using Node_type = B_tree_node<Key_type, Value_type>;
    using Raw_node_pointer = B_tree_node<Key_type, Value_type>*;
    using Node_owning_pointer = Raw_node_pointer;
    //using Node_owning_pointer = std::unique_ptr<Node_type>;
    using Node_shared_pointer = std::shared_ptr<Node_type>;
    using Shared_value_pointer = std::shared_ptr<Value_type>;
    using Shared_key_pointer = std::shared_ptr<Key_type>;
    using Size_type = std::size_t;
};

template<typename Key, typename Value>
class B_tree_node {
public:
    using Node_traits = B_tree_node_pointer_traits<Key, Value>;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;
    using Raw_key_pointer = typename Node_traits::Raw_key_pointer;
    using Raw_value_pointer = typename Node_traits::Raw_value_pointer;
    using Node_type = typename Node_traits::Node_type;
    using Raw_node_pointer = typename Node_traits::Raw_node_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Node_shared_pointer = typename Node_traits::Node_shared_pointer;
    using Size_type = typename Node_traits::Size_type;

    B_tree_node(int num_children)
            : _num_children{num_children},
              _children(static_cast<std::vector<B_tree_entry<Key_type, Value_type>>::size_type>(num_children)) {}

    B_tree_node()
            : _num_children{_max_num_children},
              _children(static_cast<std::vector<B_tree_entry<Key_type, Value_type>>::size_type>(_max_num_children)) {}

    B_tree_node(const B_tree_node&) = default;

    B_tree_node(B_tree_node&&) = default;

    ~B_tree_node() = default;

    B_tree_node& operator=(const B_tree_node&) = default;

    B_tree_node& operator=(B_tree_node&&) = default;

private:
    int _num_children;
    std::vector<B_tree_entry<Key_type, Value_type>> _children;

    template<typename, typename, typename>
    friend class B_tree;
};

template<typename Key, typename Value>
class B_tree_entry {
public:
    using Node_traits = B_tree_node_pointer_traits<Key, Value>;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;
    using Raw_key_pointer = typename Node_traits::Raw_key_pointer;
    using Raw_value_pointer = typename Node_traits::Raw_value_pointer;
    using Node_type = typename Node_traits::Node_type;
    using Raw_node_pointer = typename Node_traits::Raw_node_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Node_shared_pointer = typename Node_traits::Node_shared_pointer;
    using Size_type = typename Node_traits::Size_type;

    B_tree_entry(Key_type& key, Value_type& value, Raw_node_pointer next)
            : _key{new Key{key}},
              _value{new Value{value}},
              _next{next} {}

    B_tree_entry(Key_type& key, Raw_value_pointer value, Raw_node_pointer next)
            : _key{new Key{key}},
              _value{value},
              _next{next} {}

    B_tree_entry() = default;

    B_tree_entry(const B_tree_entry&) = default;

    B_tree_entry(B_tree_entry&&) = default;

    ~B_tree_entry() = default;

    B_tree_entry& operator=(const B_tree_entry&) = default;

    B_tree_entry& operator=(B_tree_entry&&) = default;

private:
    Raw_key_pointer _key;
    Raw_value_pointer _value;
    Raw_node_pointer _next;

    template<typename, typename, typename>
    friend class B_tree;
};

template<typename T>
struct B_tree_key_comparator {
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
class B_tree {
public:
    using Node_traits = B_tree_node_pointer_traits<Key, Value>;
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

    B_tree() : _root{new B_tree_node<Key_type, Value_type>{0}} {}

    B_tree(const B_tree&) = default;

    B_tree(B_tree&&) = default;

    ~B_tree() noexcept
    {
        _clear();
    }

    B_tree& operator=(const B_tree&) = default;

    B_tree& operator=(B_tree&&) = default;

    inline int size() const { return _num_entries; }

    inline bool is_empty() const { return size() == 0; }

    inline int height() { return _height; }

    Raw_value_pointer get(Key_type& key) const
    {
        return _search(_root, key, _height);
    }

    Raw_value_pointer get(Key_type&& key) const
    {
        return _search(_root, key, _height);
    }

    void put(Key_type& key, Value_type& val)
    {
        Raw_node_pointer u = _insert(_root, key, val, _height);
        ++_num_entries;
        if (u == nullptr) {
            return;
        }

        // need to split root
        Raw_node_pointer t{new B_tree_node<Key_type, Value_type>{2}};
        t->_children[0] = B_tree_entry<Key_type, Value_type>(_root->_children[0].key, nullptr, _root);
        t->_children[1] = B_tree_entry<Key_type, Value_type>(u->_children[0].key, nullptr, u);
        _root = t;
        ++_height;
    }

    void put(Key_type&& key, Value_type&& val)
    {
        Raw_node_pointer u = _insert(_root, key, val, _height);
        ++_num_entries;
        if (u == nullptr) {
            return;
        }

        // need to split root
        Raw_node_pointer t{new B_tree_node<Key_type, Value_type>{2}};
        t->_children[0] = B_tree_entry<Key_type, Value_type>(_root->_children[0]._key, nullptr, _root);
        t->_children[1] = B_tree_entry<Key_type, Value_type>(u->_children[0]._key, nullptr, u);
        _root = t;
        ++_height;
    }

    std::string to_string()
    {
        std::stringstream ss;
        std::string initial_indent{""};
        ss << "B_tree(\n" << _to_string(_root, _height, initial_indent) << "\n";
        return ss.str();
    }

private:
    Node_owning_pointer _root;
    int _height;
    int _num_entries;

    void _clear() noexcept
    {
        _clear(_root);
    }

    // TODO: implement
    void _clear(Node_owning_pointer& node) noexcept
    {
    }

    Raw_value_pointer _search(Raw_node_pointer n, Key_type& key, int height) const
    {
        std::vector<B_tree_entry<Key_type, Value_type>> children{n->_children};

        if (height == 0) {
            for (int j{0}; j < n->_num_children; ++j) {
                if (_eq(key, children[j].key)) { return (Value) children[j].val; }
            }
        } else {
            for (int j{0}; j < n->_num_children; ++j) {
                if (j + 1 == n->_num_children || _less(key, children[j + 1].key)) {
                    return _search(children[j].next, key, height - 1);
                }
            }
        }
        return nullptr;
    }

    Raw_node_pointer _insert(Raw_node_pointer h, Key_type& key, Value_type& val, int ht)
    {
        int j;
        B_tree_entry<Key_type, Value_type> t{key, val, nullptr};

        if (ht == 0) {
            for (j = 0; j < h->_num_children; ++j) {
                if (_less(key, h->_children[j].key)) { break; }
            }
        } else {
            for (j = 0; j < h->_num_children; ++j) {
                if ((j + 1 == h->_num_children) || _less(key, h->_children[j + 1].key)) {
                    Raw_node_pointer u{_insert(h->_children[j++].next, key, val, ht - 1)};
                    if (u == nullptr) {
                        return nullptr;
                    }
                    t._key = u->_children[0].key;
                    t._next = u;
                    break;
                }
            }
        }

        for (int i{h->_num_children}; i > j; --i) {
            h->_children[i] = h->_children[i - 1];
        }
        h->_children[j] = t;
        h->_num_children += 1;
        if (h->_num_children < _max_num_children) {
            return nullptr;
        } else {
            return _split(h);
        }
    }

    Raw_node_pointer _split(Raw_node_pointer n)
    {
        int num_children{_max_num_children / 2};
        Raw_node_pointer t{new B_tree_node<Key_type, Value_type>{num_children}};
        n->_num_children = num_children;
        for (int j{0}; j < num_children; ++j) {
            t->_children[j] = n->_children[num_children + j];
        }
        return t;
    }

    std::string _to_string(Raw_node_pointer h, int ht, std::string& indent)
    {
        std::stringstream ss;
        std::vector<B_tree_entry<Key_type, Value_type>> children{h->_children};

        if (ht == 0) {
            for (int j{0}; j < h->_num_children; ++j) {
                ss << indent << children[j].key << " " << children[j].val << "\n";
            }
        } else {
            for (int j{0}; j < h->_num_children; ++j) {
                if (j > 0) {
                    ss << indent << "(" << children[j].key << ")\n";
                }
                std::string new_indent = indent + "    ";
                ss << _to_string(children[j].next, ht - 1, new_indent);
            }
        }
        return ss.str();
    }

    bool _less(Key_type& k1, Key_type& k2) const
    {
        return k1 < k2;
    }

    bool _eq(Key_type& k1, Key_type& k2) const
    {
        return k1 == k2;
    }
};

#endif // B_TREE_H
