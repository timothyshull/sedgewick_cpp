#ifndef TST_H
#define TST_H

#include <vector>

template <typename Value>
class TST_node;

template <typename Value>
class TST;

template <typename Value>
class TST_node {
public:
    using Raw_node_pointer = TST_node*;

private:
    char c;
    Value val;
    Raw_node_pointer left;
    Raw_node_pointer mid;
    Raw_node_pointer right;
};

template <typename Value>
class TST {
public:
    using Raw_node_pointer = TST_node<Value>*;

    int size() {
        return n;
    }

    bool contains(String key) {
        return get(key) != null;
    }

    Value get(String key) {
        if (key == null) throw new NullPointerException();
        if (key.length() == 0) throw utility::Illegal_argument_exception("key must have length >= 1");
        Node<Value> x = get(root, key, 0);
        if (x == null) return null;
        return x.val;
    }

    void put(String key, Value val) {
        if (!contains(key)) n++;
        root = put(root, key, val, 0);
    }

    std::string longestPrefixOf(String query) {
        if (query == null || query.length() == 0) return null;
        int length = 0;
        Node<Value> x = root;
        int i = 0;
        while (x != null && i < query.length()) {
            char c = query.charAt(i);
            if (c < x.c) x = x.left;
            else if (c > x.c) x = x.right;
            else {
                i++;
                if (x.val != null) length = i;
                x = x.mid;
            }
        }
        return query.substring(0, length);
    }

    Iterable<std::string> keys() {
        Queue<std::string> queue = new Queue<std::string>();
        collect(root, new std::stringstream(), queue);
        return queue;
    }

    Iterable<std::string> keysWithPrefix(String prefix) {
        Queue<std::string> queue = new Queue<std::string>();
        Node<Value> x = get(root, prefix, 0);
        if (x == null) return queue;
        if (x.val != null) queue.enqueue(prefix);
        collect(x.mid, new std::stringstream(prefix), queue);
        return queue;
    }

    Iterable<std::string> keysThatMatch(String pattern) {
        Queue<std::string> queue = new Queue<std::string>();
        collect(root, new std::stringstream(), 0, pattern, queue);
        return queue;
    }
private:
    Raw_node_pointer root;
    int n;

    Node<Value> get(Node<Value> x, std::string key, int d) {
        if (key == null) throw new NullPointerException();
        if (key.length() == 0) throw utility::Illegal_argument_exception("key must have length >= 1");
        if (x == null) return null;
        char c = key.charAt(d);
        if (c < x.c) return get(x.left, key, d);
        else if (c > x.c) return get(x.right, key, d);
        else if (d < key.length() - 1) return get(x.mid, key, d + 1);
        else return x;
    }

    Node<Value> put(Node<Value> x, std::string key, Value val, int d) {
        char c = key.charAt(d);
        if (x == null) {
            x = new Node<Value>();
            x.c = c;
        }
        if (c < x.c) x.left = put(x.left, key, val, d);
        else if (c > x.c) x.right = put(x.right, key, val, d);
        else if (d < key.length() - 1) x.mid = put(x.mid, key, val, d + 1);
        else x.val = val;
        return x;
    }

    void collect(Node<Value> x, std::stringstream prefix, Queue<std::string> queue) {
        if (x == null) return;
        collect(x.left, prefix, queue);
        if (x.val != null) queue.enqueue(prefix.to_string() + x.c);
        collect(x.mid, prefix.append(x.c), queue);
        prefix.deleteCharAt(prefix.length() - 1);
        collect(x.right, prefix, queue);
    }

    void collect(Node<Value> x, std::stringstream prefix, int i, std::string pattern, Queue<std::string> queue, void) {
        if (x == null) return;
        char c = pattern.charAt(i);
        if (c == '.' || c < x.c) collect(x.left, prefix, i, pattern, queue);
        if (c == '.' || c == x.c) {
            if (i == pattern.length() - 1 && x.val != null) queue.enqueue(prefix.to_string() + x.c);
            if (i < pattern.length() - 1) {
                collect(x.mid, prefix.append(x.c), i + 1, pattern, queue);
                prefix.deleteCharAt(prefix.length() - 1);
            }
        }
        if (c == '.' || c > x.c) collect(x.right, prefix, i, pattern, queue);
    }
};

#endif // TST_H
