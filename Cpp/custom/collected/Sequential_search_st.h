#ifndef SEQUENTIAL_SEARCH_ST_H
#define SEQUENTIAL_SEARCH_ST_H

#include <vector>

#include "utility.h"
#include "Queue.h"

template<typename Key, typename Value>
class Sequential_search_st_node;

template<typename Key, typename Value>
class Sequential_search_st;

template<typename Key, typename Value>
class Sequential_search_st_node {
public:
    using Key_type = Key;
    using Value_type = Value;
    using Owning_node_pointer = Sequential_search_st_node<Key_type, Value_type>*;

    Sequential_search_st_node(Key_type& key, Value_type& value, Owning_node_pointer next) : key{key}, val{value}, next{next} {}

private:
    Key_type key;
    Value_type val;
    Owning_node_pointer next;

    template<typename, typename>
    friend class Sequential_search_st;
};

template<typename Key, typename Value>
class Sequential_search_st {
public:
    using Key_type = Key;
    using Value_type = Value;
    using Node = Sequential_search_st_node<Key_type, Value_type>;
    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;

    Sequential_search_st() = default;

    inline int size() const noexcept { return _size; }

    inline bool is_empty() const noexcept { return _size == 0; }

    bool contains(Key_type& key)
    {
        if (key == nullptr) { throw utility::Null_pointer_exception{"argument to contains() is nullptr"}; }
        return get(key) != nullptr;
    }

    Value get(Key_type& key)
    {
        if (key == nullptr) { throw utility::Null_pointer_exception{"argument to get() is nullptr"}; }
        for (Raw_node_pointer x{_first}; x != nullptr; x = x->next) {
            if (key == x->key) {
                return x->val;
            }
        }
        return nullptr;
    }

    void put(Key_type& key, Value_type& val)
    {
        if (key == nullptr) { throw utility::Null_pointer_exception{"first argument to put() is nullptr"}; }
        if (val == nullptr) {
            delete (key);
            return;
        }

        for (Raw_node_pointer x{_first}; x != nullptr; x = x->next) {
            if (key == x->key) {
                x->val = val;
                return;
            }
        }
        _first = new Sequential_search_st_node{key, val, _first};
        ++_size;
    }

    void remove(Key key)
    {
        if (key == nullptr) { throw utility::Null_pointer_exception{"argument to delete() is nullptr"}; }
        _first = remove(_first, key);
    }

    Queue<Key_type> keys()
    {
        Queue<Key> queue;
        for (Raw_node_pointer x{_first}; x != nullptr; x = x->next) {
            queue.enqueue(x->key);
        }
        return queue;
    }

private:
    int _size;
    Owning_node_pointer _first;

    Raw_node_pointer remove(Raw_node_pointer x, Key key)
    {
        if (x == nullptr) { return nullptr; }
        if (key == x->key) {
            _size--;
            return x->next;
        }
        x->next = remove(x->next, key);
        return x;
    }
};

#endif // SEQUENTIAL_SEARCH_ST_H
