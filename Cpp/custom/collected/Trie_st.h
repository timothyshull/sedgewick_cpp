#ifndef TRIE_ST_H
#define TRIE_ST_H

#include <vector>
#include "Queue.h"

const static int R = 256;

template <typename Value>
class Trie_st_node;

template <typename Value>
class Trie_st;

template <typename Value>
class Trie_st_node {
public:
    using Raw_node_pointer = Trie_st_node*;

    Trie_st_node() : next(static_cast<std::vector<Raw_node_pointer>::size_type>(R)), val{} {}

private:
    Value val;
    std::vector<Raw_node_pointer> next;
};

template <typename Value>
class Trie_st {
public:
    using Raw_node_pointer = Trie_st_node*;

    Trie_st();



Value get(String key) {
        Node x = get(root, key, 0);
        if (x == null) return null;
        return (Value) x.val;
    }

    bool contains(String key) {
        return get(key) != null;
    }

void put(String key, Value val) {
        if (val == null) delete(key);
        else root = put(root, key, val, 0);
    }

int size() {
        return n;
    }

    bool is_empty() {
        return size() == 0;
    }

    Iterable<std::string> keys() {
        return keysWithPrefix("");
    }

    Iterable<std::string> keysWithPrefix(String prefix) {
        Queue<std::string> results = new Queue<std::string>();
        Node x = get(root, prefix, 0);
        collect(x, new std::stringstream(prefix), results);
        return results;
    }

    Iterable<std::string> keysThatMatch(String pattern) {
        Queue<std::string> results = new Queue<std::string>();
        collect(root, new std::stringstream(), pattern, results);
        return results;
    }

    std::string longestPrefixOf(String query) {
        int length = longestPrefixOf(root, query, 0, -1);
        if (length == -1) return null;
        else return query.substring(0, length);
    }

    void remove(String key) {
        root = remove(root, key, 0);
    }
private:
    Raw_node_pointer root;
    int n;

Node get(Node x, std::string key, int d) {
        if (x == null) return null;
        if (d == key.length()) return x;
        char c = key.charAt(d);
        return get(x.next[c], key, d + 1);
    }

Node put(Node x, std::string key, Value val, int d) {
        if (x == null) x = new Node();
        if (d == key.length()) {
            if (x.val == null) ++n;
            x.val = val;
            return x;
        }
        char c = key.charAt(d);
        x.next[c] = put(x.next[c], key, val, d + 1);
        return x;
    }

    void collect(Node x, std::stringstream prefix, Queue<std::string> results) {
        if (x == null) return;
        if (x.val != null) results.enqueue(prefix.to_string());
        for (char c{0}; c < R; ++c) {
            prefix.append(c);
            collect(x.next[c], prefix, results);
            prefix.deleteCharAt(prefix.length() - 1);
        }
    }

    void collect(Node x, std::stringstream prefix, std::string pattern, Queue<std::string> results) {
        if (x == null) return;
        int d = prefix.length();
        if (d == pattern.length() && x.val != null)
            results.enqueue(prefix.to_string());
        if (d == pattern.length())
            return;
        char c = pattern.charAt(d);
        if (c == '.') {
            for (char ch{0}; ch < R; ++ch) {
                prefix.append(ch);
                collect(x.next[ch], prefix, pattern, results);
                prefix.deleteCharAt(prefix.length() - 1);
            }
        } else {
            prefix.append(c);
            collect(x.next[c], prefix, pattern, results);
            prefix.deleteCharAt(prefix.length() - 1);
        }
    }

    int longestPrefixOf(Node x, std::string query, int d, int length) {
        if (x == null) return length;
        if (x.val != null) length = d;
        if (d == query.length()) return length;
        char c = query.charAt(d);
        return longestPrefixOf(x.next[c], query, d + 1, length);
    }

    Node remove(Node x, std::string key, int d) {
        if (x == null) return null;
        if (d == key.length()) {
            if (x.val != null) n--;
            x.val = null;
        } else {
            char c = key.charAt(d);
            x.next[c] = delete(x.next[c], key, d + 1);
        }

        // remove subtrie rooted at x if it is completely empty
        if (x.val != null) return x;
        for (int c{0}; c < R; ++c)
            if (x.next[c] != null)
                return x;
        return null;
    }
};

#endif // TRIE_ST_H
