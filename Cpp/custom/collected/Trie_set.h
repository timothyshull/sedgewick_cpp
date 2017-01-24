#ifndef TRIE_SET_H
#define TRIE_SET_H

#include <vector>
#include "Queue.h"

const static int R = 256;

class Trie_set_node;

class Trie_set;

class Trie_set_node {
public:
    using Raw_node_pointer = Trie_set_node*;

    Trie_set_node() : next(static_cast<std::vector<Raw_node_pointer>::size_type>(R)), isString{false} {}

private:
    std::vector<Raw_node_pointer> next;
    bool isString;
};

class Trie_set {
public:
    using Raw_node_pointer = Trie_set_node*;

    Trie_set();

    bool contains(std::string& key);

    void add(std::string& key);

    int size();

    bool isEmpty();

    std::vector<std::string> iterator();

    std::vector<std::string> keysWithPrefix();

    std::vector<std::string> keysThatMatch();

    std::string longestPrefixOf(std::string& query);

    void remove(std::string& key);

private:
    Raw_node_pointer root;
    int n;

    Raw_node_pointer get(Raw_node_pointer x, std::string& key, int d);

    Raw_node_pointer add(Raw_node_pointer x, std::string& key, int d);

    void collect(Raw_node_pointer x, std::stringstream& prefix, Queue<std::string>& results);

    void collect(Raw_node_pointer x, std::stringstream& pattern, Queue<std::string>& results, void);

    int longestPrefixOf(Raw_node_pointer x, std::string& query, int d, int length);

    Raw_node_pointer remove(Raw_node_pointer x, std::string& key, int d);
};

#endif // TRIE_SET_H
