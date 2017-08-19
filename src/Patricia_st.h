#ifndef PATRICIA_ST_H
#define PATRICIA_ST_H

#include <string>
#include <vector>

#include "utility.h"
#include "Queue.h"

template<typename Value>
class Patricia_st;

template<typename Value>
class Patricia_st_node;

template<typename Value>
class Patricia_st_node {
public:
    using Raw_node_pointer = Patricia_st_node*;

    Patricia_st_node(std::string& key, Value& val, int b) : key{key}, val{val}, b{b} {}

    Patricia_st_node(std::string&& key, Value& val, int b) : key{key}, val{val}, b{b} {}

private:
    Raw_node_pointer left;
    Raw_node_pointer right;
    std::string key;
    Value val;
    int b;

    template<typename>
    friend class Patricia_st;
};

template<typename Value>
class Patricia_st {
public:
    using Raw_node_pointer = Patricia_st_node<Value>*;

    Patricia_st()
    {
        _head = new Patricia_st_node("", nullptr, 0);
        _head->left = _head;
        _head->right = _head;
        _count = 0;
    }

    void put(std::string& key, Value val)
    {
        if (key == nullptr) { throw utility::Null_pointer_exception{"called put(nullptr)"}; }
        if (key.length() == 0) { throw utility::Illegal_argument_exception{"invalid key"}; }
        if (val == nullptr) { delete (key); }
        Raw_node_pointer p;
        Raw_node_pointer x = _head;
        do {
            p = x;
            if (_safe_bit_test(key, x->b)) { x = x->right; }
            else { x = x->left; }
        } while (p->b < x->b);
        if (x->key != key) {
            int b = _first_differing_bit(x->key, key);
            x = _head;
            do {
                p = x;
                if (_safe_bit_test(key, x->b)) { x = x->right; }
                else { x = x->left; }
            } while (p->b < x->b && x->b < b);
            Raw_node_pointer t = new Patricia_st_node(key, val, b);
            if (_safe_bit_test(key, b)) {
                t->left = x;
                t->right = t;
            } else {
                t->left = t;
                t->right = x;
            }
            if (_safe_bit_test(key, p->b)) { p->right = t; }
            else { p->left = t; }
            ++_count;
        } else { x->val = val; }
    }

    Value get(std::string& key)
    {
        if (key == nullptr) { throw utility::Null_pointer_exception{"called get(nullptr)"}; }
        if (key.length() == 0) { throw utility::Illegal_argument_exception{"invalid key"}; }
        Raw_node_pointer p;
        Raw_node_pointer x = _head;
        do {
            p = x;
            if (_safe_bit_test(key, x->b)) { x = x->right; }
            else { x = x->left; }
        } while (p->b < x->b);
        if (x->key == key) { return x->val; }
        else { return nullptr; }
    }

    void remove(std::string& key)
    {
        if (key == nullptr) { throw utility::Null_pointer_exception{"called delete(nullptr)"}; }
        if (key.length() == 0) { throw utility::Illegal_argument_exception{"invalid key"}; }
        Raw_node_pointer g;
        Raw_node_pointer p = _head;
        Raw_node_pointer x = _head;
        do {
            g = p;
            p = x;
            if (_safe_bit_test(key, x->b)) { x = x->right; }
            else { x = x->left; }
        } while (p->b < x->b);
        if (x->key == key) {
            Raw_node_pointer z;
            Raw_node_pointer y = _head;
            do {
                z = y;
                if (_safe_bit_test(key, y->b)) { y = y->right; }
                else { y = y->left; }
            } while (y != x);
            if (x == p) {
                Raw_node_pointer c;
                if (_safe_bit_test(key, x->b)) { c = x->left; }
                else { c = x->right; }
                if (_safe_bit_test(key, z->b)) { z->right = c; }
                else { z->left = c; }
            } else {
                Raw_node_pointer c;
                if (_safe_bit_test(key, p->b)) { c = p->left; }
                else { c = p->right; }
                if (_safe_bit_test(key, g->b)) { g->right = c; }
                else { g->left = c; }
                if (_safe_bit_test(key, z->b)) { z->right = p; }
                else { z->left = p; }
                p->left = x->left;
                p->right = x->right;
                p->b = x->b;
            }
            _count--;
        }
    }

    inline bool contains(std::string& key) const { return get(key) != nullptr; }

    inline bool contains(std::string&& key) const { return get(key) != nullptr; }

    inline bool is_empty() const { return _count == 0; }

    inline int size() const { return _count; }

    Queue<std::string> keys()
    {
        Queue<std::string> queue;
        if (_head->left != _head) { _keys(_head->left, 0, queue); }
        if (_head->right != _head) { _keys(_head->right, 0, queue); }
        return queue;
    }

private:
    Raw_node_pointer _head;
    int _count;

    void _keys(Raw_node_pointer x, int b, Queue<std::string>& queue)
    {
        if (x->b > b) {
            _keys(x->left, x->b, queue);
            queue.enqueue(x->key);
            _keys(x->right, x->b, queue);
        }
    }

    static bool _safe_bit_test(std::string& key, int b)
    {
        if (b < key.length() * 16) { return _bit_test(key, b) != 0; }
        return b <= key.length() * 16 + 15;
    }

    static int _bit_test(std::string& key, int b)
    {
        return (key[b >> 4] >> (b & 0xf)) & 1;
    }

    static int _safe_char_at(std::string& key, int i)
    {
        if (i < key.length()) { return key[i]; }
        if (i > key.length()) {
            return 0x0000;
        } else { return 0xffff; }
    }

    static int _first_differing_bit(std::string& k1, std::string& k2)
    {
        int i = 0;
        int c1 = _safe_char_at(k1, 0) & ~1;
        int c2 = _safe_char_at(k2, 0) & ~1;
        if (c1 == c2) {
            i = 1;
            while (_safe_char_at(k1, i) == _safe_char_at(k2, i)) { ++i; }
            c1 = _safe_char_at(k1, i);
            c2 = _safe_char_at(k2, i);
        }
        int b = 0;
        while (((c1 >> b) & 1) == ((c2 >> b) & 1)) { ++b; }
        return i * 16 + b;
    }
};

#endif // PATRICIA_ST_H
