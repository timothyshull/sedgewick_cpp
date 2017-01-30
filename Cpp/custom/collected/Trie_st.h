#ifndef TRIE_ST_H
#define TRIE_ST_H

#include <vector>
#include "Queue.h"

template<typename Value>
class Trie_st_node;

template<typename Value>
class Trie_st;

template<typename Value>
class Trie_st_node {
public:
    using Raw_node_pointer = Trie_st_node*;

    Trie_st_node() : _next(static_cast<std::vector<Raw_node_pointer>::size_type>(Trie_st::_radix)), _val{} {}

private:
    Value _val;
    std::vector<Raw_node_pointer> _next;

    template<typename>
    friend class Trie_st;
};

template<typename Value>
class Trie_st {
public:
    using Raw_node_pointer = Trie_st_node*;
    using Value_type = Value;

    Trie_st() = default;

    Value get(std::string& key)
    {
        Raw_node_pointer x = _get(_root, key, 0);
        if (x == nullptr) { return nullptr; }
        return (Value) x->_val;
    }

    inline bool contains(std::string& key) const { return get(key) != nullptr; }

    void put(std::string& key, Value val)
    {
        if (val == nullptr) { delete (key); }
        else { _root = _put(_root, key, val, 0); }
    }

    inline int size() const noexcept { return _size; }

    inline bool is_empty() const noexcept { return size() == 0; }

    Queue<std::string> keys()
    {
        std::string s{""};
        return keys_with_prefix(s);
    }

    Queue<std::string> keys_with_prefix(std::string& prefix)
    {
        Queue<std::string> results;
        Raw_node_pointer x = _get(_root, prefix, 0);
        _collect(x, std::stringstream{prefix}, results);
        return results;
    }

    Queue<std::string> keys_that_match(std::string& pattern)
    {
        Queue<std::string> results;
        std::stringstream ss;
        _collect(_root, ss, pattern, results);
        return results;
    }

    std::string longest_prefix_of(std::string& query)
    {
        int length = _longest_prefix_of(_root, query, 0, -1);
        if (length == -1) { return nullptr; }
        else { return query.substr(0, length); }
    }

    void remove(std::string& key)
    {
        _root = _remove(_root, key, 0);
    }

private:
    const static int _radix = 256;
    Raw_node_pointer _root;
    int _size;

    template<typename>
    friend class Trie_st_node;

    Raw_node_pointer _get(Raw_node_pointer x, std::string key, int d)
    {
        if (x == nullptr) { return nullptr; }
        if (d == key.length()) { return x; }
        char c = key[d];
        return _get(x->_next[c], key, d + 1);
    }

    Raw_node_pointer _put(Raw_node_pointer x, std::string key, Value val, int d)
    {
        if (x == nullptr) { x = new Trie_st_node{}; }
        if (d == key.length()) {
            if (x->_val == nullptr) { ++_size; }
            x->_val = val;
            return x;
        }
        char c = key[d];
        x->_next[c] = _put(x->_next[c], key, val, d + 1);
        return x;
    }

    void _collect(Raw_node_pointer x, std::stringstream prefix, Queue<std::string> results)
    {
        if (x == nullptr) { return; }
        if (x->_val != nullptr) {
            std::string s{prefix.str()};
            results.enqueue(s);
        }
        for (char c{0}; c < _radix; ++c) {
            prefix << c;
            _collect(x->_next[c], prefix, results);
            std::string s{prefix.str()};
            s.erase(s.size() - 1);
            prefix.str(s);
        }
    }

    void _collect(Raw_node_pointer x, std::stringstream prefix, std::string pattern, Queue<std::string> results)
    {
        if (x == nullptr) { return; }
        auto d = prefix.str().size();
        if (d == pattern.length() && x->_val != nullptr) {
            std::string s{prefix.str()};
            results.enqueue(s);
        }
        if (d == pattern.length()) {
            return;
        }
        char c = pattern[d];
        if (c == '.') {
            for (char ch{0}; ch < _radix; ++ch) {
                prefix << ch;
                _collect(x->_next[ch], prefix, pattern, results);
                std::string s{prefix.str()};
                s.erase(s.size() - 1);
                prefix.str(s);
            }
        } else {
            prefix << c;
            _collect(x->_next[c], prefix, pattern, results);
            std::string s{prefix.str()};
            s.erase(s.size() - 1);
            prefix.str(s);
        }
    }

    int _longest_prefix_of(Raw_node_pointer x, std::string query, int d, int length)
    {
        if (x == nullptr) { return length; }
        if (x->_val != nullptr) { length = d; }
        if (d == query.length()) { return length; }
        char c = query[d];
        return _longest_prefix_of(x->_next[c], query, d + 1, length);
    }

    Raw_node_pointer _remove(Raw_node_pointer x, std::string key, int d)
    {
        if (x == nullptr) { return nullptr; }
        if (d == key.length()) {
            if (x->_val != nullptr) { _size--; }
            x->_val = nullptr;
        } else {
            char c = key[d];
            x->_next[c] = delete (x->_next[c], key, d + 1);
        }

        if (x->_val != nullptr) { return x; }
        for (int c{0}; c < _radix; ++c) {
            if (x->_next[c] != nullptr) {
                return x;
            }
        }
        return nullptr;
    }

};

#endif // TRIE_ST_H
