#include "Trie_set.h"

Trie_set::Trie_set() : _root{nullptr}, _size{0} {}

bool Trie_set::contains(std::string& key)
{
    Raw_node_pointer x = _get(_root, key, 0);
    if (x == nullptr) { return false; }
    return x->_is_string;
}

void Trie_set::add(std::string& key)
{
    _root = _add(_root, key, 0);
}

std::vector<std::string> Trie_set::iterator()
{
    std::string s{""};
    return keys_with_prefix(s).iterator();
}

Queue<std::string> Trie_set::keys_with_prefix(std::string& prefix)
{
    Queue<std::string> results;
    Raw_node_pointer x = _get(_root, prefix, 0);
    std::stringstream ss{prefix};
    _collect(x, ss, results);
    return results;
}

Queue<std::string> Trie_set::keys_that_match(std::string& pattern)
{
    Queue<std::string> results;
    std::stringstream prefix;
    _collect(_root, prefix, pattern, results);
    return results;
}

std::string Trie_set::longest_prefix_of(std::string& query)
{
    int length = _longest_prefix_of(_root, query, 0, -1);
    if (length == -1) { return nullptr; }
    return query.substr(0, length);
}

void Trie_set::remove(std::string& key)
{
    _root = _remove(_root, key, 0);
}

Trie_set::Raw_node_pointer Trie_set::_get(Trie_set::Raw_node_pointer x, std::string& key, int d)
{
    if (x == nullptr) { return nullptr; }
    if (d == key.length()) { return x; }
    char c = key[d];
    return _get(x->_next[c], key, d + 1);
}

Trie_set::Raw_node_pointer Trie_set::_add(Trie_set::Raw_node_pointer x, std::string& key, int d)
{
    if (x == nullptr) { x = new Trie_set_node{}; }
    if (d == key.length()) {
        if (!x->_is_string) { ++_size; }
        x->_is_string = true;
    } else {
        char c = key[d];
        x->_next[c] = _add(x->_next[c], key, d + 1);
    }
    return x;
}

void Trie_set::_collect(Trie_set::Raw_node_pointer x, std::stringstream& prefix, Queue<std::string>& results)
{
    if (x == nullptr) { return; }
    if (x->_is_string) {
        std::string s{prefix.str()};
        results.enqueue(s); }
    for (char c{0}; c < _radix; ++c) {
        prefix << c;
        _collect(x->_next[c], prefix, results);
        std::string s{prefix.str()};
        s.erase(s.size() - 1);
        prefix.str(s);
    }
}

void Trie_set::_collect(Trie_set::Raw_node_pointer x, std::stringstream& prefix, std::string& pattern, Queue<std::string>& results)
{
    if (x == nullptr) { return; }
    auto d = prefix.str().size();
    if (d == pattern.length() && x->_is_string) {
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

int Trie_set::_longest_prefix_of(Trie_set::Raw_node_pointer x, std::string& query, int d, int length)
{
    if (x == nullptr) { return length; }
    if (x->_is_string) { length = d; }
    if (d == query.length()) { return length; }
    char c = query[d];
    return _longest_prefix_of(x->_next[c], query, d + 1, length);
}

Trie_set::Raw_node_pointer Trie_set::_remove(Trie_set::Raw_node_pointer x, std::string& key, int d)
{
    if (x == nullptr) { return nullptr; }
    if (d == key.length()) {
        if (x->_is_string) { --_size; }
        x->_is_string = false;
    } else {
        char c = key[d];
        x->_next[c] = _remove(x->_next[c], key, d + 1);
    }

    if (x->_is_string) { return x; }
    for (int c{0}; c < _radix; ++c) {
        if (x->_next[c] != nullptr) {
            return x;
        }
    }
    return nullptr;
}
