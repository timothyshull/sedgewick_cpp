#ifndef SEQUENTIAL_SEARCH_ST_H
#define SEQUENTIAL_SEARCH_ST_H

#include <vector>

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
};

template<typename Key, typename Value>
class Sequential_search_st {
public:
    using Key_type = Key;
    using Value_type = Value;
    using Owning_node_pointer = Sequential_search_st_node<Key_type, Value_type>*;

    SequentialSearchST() {}

    int size()
    {
        return n;
    }

    bool is_empty()
    {
        return size() == 0;
    }

    bool contains(Key key)
    {
        if (key == null) { throw new NullPointerException("argument to contains() is null"); }
        return get(key) != null;
    }

    Value get(Key key)
    {
        if (key == null) { throw new NullPointerException("argument to get() is null"); }
        for (Node x{first}; x != null; x = x.next) {
            if (key.equals(x.key)) {
                return x.val;
            }
        }
        return null;
    }

    void put(Key key, Value val)
    {
        if (key == null) { throw new NullPointerException("first argument to put() is null"); }
        if (val == null) {
            delete (key);
            return;
        }

        for (Node x{first}; x != null; x = x.next) {
            if (key.equals(x.key)) {
                x.val = val;
                return;
            }
        }
        first = new Node(key, val, first);
        ++n;
    }

    void remove(Key key)
    {
        if (key == null) { throw new NullPointerException("argument to delete() is null"); }
        first = remove(first, key);
    }

    std::vector<Key_type> keys() {
        Queue<Key> queue = new Queue<Key>();
        for (Node x{first}; x != null; x = x.next)
            queue.enqueue(x.key);
        return queue;
    }

private:
    int n;
    Owning_node_pointer first;

    Node remove(Node x, Key key)
    {
        if (x == null) { return null; }
        if (key.equals(x.key)) {
            n--;
            return x.next;
        }
        x.next = delete (x.next, key);
        return x;
    }
};

#endif // SEQUENTIAL_SEARCH_ST_H
