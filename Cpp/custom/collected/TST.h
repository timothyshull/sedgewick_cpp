#ifndef TST_H
#define TST_H

#include <vector>
#include <string>
#include "utility.h"
#include "Queue.h"

template<typename Value>
class TST_node;

template<typename Value>
class TST;

template<typename Value>
class TST_node {
public:
    using Raw_node_pointer = TST_node*;

private:
    char c;
    Value val;
    Raw_node_pointer left;
    Raw_node_pointer mid;
    Raw_node_pointer right;

    template<typename>
    friend class TST;
};

template<typename Value>
class TST {
public:
    using Raw_node_pointer = TST_node<Value>*;

    int size()
    {
        return n;
    }

    bool contains(std::string& key)
    {
        return get(key) != nullptr;
    }

    Value get(std::string& key)
    {
        if (key == nullptr) { throw utility::Null_pointer_exception{""}; }
        if (key.size() == 0) { throw utility::Illegal_argument_exception("key must have length >= 1"); }
        Raw_node_pointer x = get(root, key, 0);
        if (x == nullptr) { return nullptr; }
        return x->val;
    }

    void put(std::string& key, Value val)
    {
        if (!contains(key)) { ++n; }
        root = put(root, key, val, 0);
    }

    std::string longestPrefixOf(std::string& query)
    {
        if (query == nullptr || query.size() == 0) { return nullptr; }
        int length = 0;
        Raw_node_pointer x = root;
        int i = 0;
        while (x != nullptr && i < query.size()) {
            char c = query[i];
            if (c < x->c) { x = x->left; }
            else if (c > x->c) { x = x->right; }
            else {
                ++i;
                if (x->val != nullptr) { length = i; }
                x = x->mid;
            }
        }
        return query.substr(0, length);
    }

    Iterable <std::string> keys()
    {
        Queue<std::string> queue = new Queue<std::string>();
        collect(root, new std::stringstream(), queue);
        return queue;
    }

    Iterable <std::string> keysWithPrefix(std::string& prefix)
    {
        Queue<std::string> queue = new Queue<std::string>();
        Raw_node_pointer x = get(root, prefix, 0);
        if (x == nullptr) { return queue; }
        if (x->val != nullptr) { queue.enqueue(prefix); }
        collect(x->mid, new std::stringstream(prefix), queue);
        return queue;
    }

    Iterable <std::string> keysThatMatch(std::string& pattern)
    {
        Queue<std::string> queue = new Queue<std::string>();
        collect(root, new std::stringstream(), 0, pattern, queue);
        return queue;
    }

private:
    Raw_node_pointer root;
    int n;

    Raw_node_pointer get(Raw_node_pointer x, std::string& key, int d)
    {
        if (key == nullptr) { throw utility::Null_pointer_exception{""}; }
        if (key.size() == 0) { throw utility::Illegal_argument_exception("key must have length >= 1"); }
        if (x == nullptr) { return nullptr; }
        char c = key[d];
        if (c < x->c) { return get(x->left, key, d); }
        else if (c > x->c) { return get(x->right, key, d); }
        else if (d < key.size() - 1) { return get(x->mid, key, d + 1); }
        else { return x; }
    }

    Raw_node_pointer put(Raw_node_pointer x, std::string key, Value val, int d)
    {
        char c = key[d];
        if (x == nullptr) {
            x = new Raw_node_pointer();
            x->c = c;
        }
        if (c < x->c) { x->left = put(x->left, key, val, d); }
        else if (c > x->c) { x->right = put(x->right, key, val, d); }
        else if (d < key.size() - 1) { x->mid = put(x->mid, key, val, d + 1); }
        else { x->val = val; }
        return x;
    }

    void collect(Raw_node_pointer x, std::stringstream prefix, Queue<std::string> queue)
    {
        if (x == nullptr) { return; }
        collect(x->left, prefix, queue);
        if (x->val != nullptr) { queue.enqueue(prefix.to_string() + x->c); }
        collect(x->mid, prefix.append(x->c), queue);
        prefix.deleteCharAt(prefix.size() - 1);
        collect(x->right, prefix, queue);
    }

    void collect(Raw_node_pointer x, std::stringstream prefix, int i, std::string pattern, Queue<std::string> queue, void)
    {
        if (x == nullptr) { return; }
        char c = pattern[i];
        if (c == '.' || c < x->c) { collect(x->left, prefix, i, pattern, queue); }
        if (c == '.' || c == x->c) {
            if (i == pattern.size() - 1 && x->val != nullptr) { queue.enqueue(prefix.to_string() + x->c); }
            if (i < pattern.size() - 1) {
                collect(x->mid, prefix.append(x->c), i + 1, pattern, queue);
                prefix.deleteCharAt(prefix.size() - 1);
            }
        }
        if (c == '.' || c > x->c) { collect(x->right, prefix, i, pattern, queue); }
    }
};

#endif // TST_H
