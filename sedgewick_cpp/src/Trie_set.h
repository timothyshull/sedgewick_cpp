#ifndef TRIE_Set_H
#define TRIE_Set_H

#include <vector>
#include "Queue.h"

class Trie_set_node;

class Trie_set;

class Trie_set_node {
public:
    using Raw_node_pointer = Trie_set_node*;

    Trie_set_node() : _next(static_cast<std::vector<Raw_node_pointer>::size_type>(Trie_set::_radix)), _is_string{false} {}

private:
    std::vector<Raw_node_pointer> _next;
    bool _is_string;

    friend class Trie_set;
};

class Trie_set {
public:
    using Raw_node_pointer = Trie_set_node*;

    Trie_set();

    bool contains(std::string& key);

    void add(std::string& key);

    inline int size() const noexcept { return _size; }

    inline bool is_empty() const noexcept { return size() == 0; }

    std::vector<std::string> iterator();

    Queue keys_with_prefix(std::string& prefix);

    Queue<std::string> keys_that_match(std::string& pattern);

    std::string longest_prefix_of(std::string& query);

    void remove(std::string& key);

private:
    const static int _radix = 256;
    Raw_node_pointer _root;
    int _size;

    Raw_node_pointer _get(Raw_node_pointer x, std::string& key, int d);

    Raw_node_pointer _add(Raw_node_pointer x, std::string& key, int d);

    void _collect(Raw_node_pointer x, std::stringstream& prefix, Queue<std::string>& results);

    void _collect(Raw_node_pointer x, std::stringstream& prefix, std::string& pattern, Queue<std::string>& results);

    int _longest_prefix_of(Raw_node_pointer x, std::string& query, int d, int length);

    Raw_node_pointer _remove(Raw_node_pointer x, std::string& key, int d);

    friend class Trie_set_node;
};

#endif // TRIE_Set_H
