#include "Patricia_set.h"

Patricia_set_node::Patricia_set_node(std::string& key, int b) : key{key}, b{b} {}

Patricia_set_node::Patricia_set_node(std::string&& key, int b) : key{key}, b{b} {}

Patricia_set::Patricia_set() : count{0}
{
    head = new Patricia_set_node{"", 0};
    head->left = head;
    head->right = head;
}

void Patricia_set::add(std::string& key)
{
    if (key == nullptr) { throw utility::Null_pointer_exception{"called add(nullptr)"}; }
    if (key.size() == 0) { throw utility::Illegal_argument_exception{"invalid key"}; }
    Raw_node_pointer p;
    Raw_node_pointer x{head};

    do {
        p = x;
        if (_safe_bit_test(key, x->b)) { x = x->right; }
        else { x = x->left; }
    } while (p->b < x->b);

    if (x->key != key) {
        int b = _first_differing_bit(x->key, key);
        x = head;

        do {
            p = x;
            if (_safe_bit_test(key, x->b)) { x = x->right; }
            else { x = x->left; }
        } while (p->b < x->b && x->b < b);

        Raw_node_pointer t{new Patricia_set_node{key, b}};

        if (_safe_bit_test(key, b)) {
            t->left = x;
            t->right = t;
        } else {
            t->left = t;
            t->right = x;
        }

        if (_safe_bit_test(key, p->b)) { p->right = t; }
        else { p->left = t; }
        ++count;
    }
}

bool Patricia_set::contains(std::string& key)
{
    if (key == nullptr) { throw utility::Null_pointer_exception{"called contains(nullptr)"}; }
    if (key.size() == 0) { throw utility::Illegal_argument_exception{"invalid key"}; }
    Raw_node_pointer p;
    Raw_node_pointer x = head;
    do {
        p = x;
        if (_safe_bit_test(key, x->b)) { x = x->right; }
        else { x = x->left; }
    } while (p->b < x->b);
    return x->key == key;
}

void Patricia_set::remove(std::string& key)
{
    if (key == nullptr) { throw utility::Null_pointer_exception{"called delete(nullptr)"}; }
    if (key.size() == 0) { throw utility::Illegal_argument_exception{"invalid key"}; }
    Raw_node_pointer g;             // previous previous (grandparent)
    Raw_node_pointer p = head;      // previous (parent)
    Raw_node_pointer x = head;      // node to delete
    do {
        g = p;
        p = x;
        if (_safe_bit_test(key, x->b)) { x = x->right; }
        else { x = x->left; }
    } while (p->b < x->b);
    if (x->key == key) {
        Raw_node_pointer z;
        Raw_node_pointer y = head;
        do {            // find the true parent (z) of x
            z = y;
            if (_safe_bit_test(key, y->b)) { y = y->right; }
            else { y = y->left; }
        } while (y != x);
        if (x == p) {   // case 1: remove (leaf node) x
            Raw_node_pointer c;     // child of x
            if (_safe_bit_test(key, x->b)) { c = x->left; }
            else { c = x->right; }
            if (_safe_bit_test(key, z->b)) { z->right = c; }
            else { z->left = c; }
        } else {          // case 2: p replaces (internal node) x
            Raw_node_pointer c;     // child of p
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
        count--;
    }
}

bool Patricia_set::is_empty()
{
    return count == 0;
}

int Patricia_set::size()
{
    return count;
}

std::string Patricia_set::to_string()
{
    std::stringstream ss;
    for (auto key : *this) { ss << key << " "; }
    std::string s{ss.str()};
    if (s.size() > 0) {
        s.erase(s.begin() + (s.size() - 1));
    }
    return s;
}

void Patricia_set::_collect(Patricia_set::Raw_node_pointer x, int b, Queue<std::string> queue)
{
    if (x->b > b) {
        _collect(x->left, x->b, queue);
        queue.enqueue(x->key);
        _collect(x->right, x->b, queue);
    }
}

bool Patricia_set::_safe_bit_test(std::string& key, int b)
{
    if (b < key.size() * 16) { return _bit_test(key, b) != 0; }
    if (b > key.size() * 16 + 15) { return false; }   // padding
    /* 16 bits of 0xffff */
    return true;
}

int Patricia_set::_bit_test(std::string& key, int b)
{
    return (key[b >> 4] >> (b & 0xf)) & 1;
}

int Patricia_set::_safe_char_at(std::string& key, int i)
{
    if (i < key.size()) { return key[i]; }
    if (i > key.size()) {
        return 0x0000;            // padding
    } else { return 0xffff; }
}

int Patricia_set::_first_differing_bit(std::string& k1, std::string& k2)
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
