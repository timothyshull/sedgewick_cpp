#ifndef PATRICIA_ST_H
#define PATRICIA_ST_H

#include <string>
#include <vector>

template<typename Value>
class Patricia_st;

template<typename Value>
class Patricia_st_node;

template<typename Value>
class Patricia_st_node {
public:
    using Raw_node_pointer = Patricia_st_node*;

    Patricia_st_node(std::string& key, Value& val, int b) : key{key}, val{val}, b{b} {}

private:
    Raw_node_pointer left;
    Raw_node_pointer right;
    std::string key;
    Value val;
    int b;
};

template<typename Value>
class Patricia_st {
public:
    using Raw_node_pointer = Patricia_st_node<Value>*;

    Patricia_st() {
        head = new Node("", null, 0);
        head.left = head;
        head.right = head;
        count = 0;
    }

void put(String key, Value val) {
        if (key == null) throw new NullPointerException("called put(null)");
        if (key.length() == 0) throw new IllegalArgumentException("invalid key");
        if (val == null) delete(key);
        Node p;
        Node x = head;
        do {
            p = x;
            if (safeBitTest(key, x.b)) x = x.right;
            else x = x.left;
        } while (p.b < x.b);
        if (!x.key.equals(key)) {
            int b = firstDifferingBit(x.key, key);
            x = head;
            do {
                p = x;
                if (safeBitTest(key, x.b)) x = x.right;
                else x = x.left;
            } while (p.b < x.b && x.b < b);
            Node t = new Node(key, val, b);
            if (safeBitTest(key, b)) {
                t.left = x;
                t.right = t;
            } else {
                t.left = t;
                t.right = x;
            }
            if (safeBitTest(key, p.b)) p.right = t;
            else p.left = t;
            count++;
        } else x.val = val;
    }


Value get(String key) {
        if (key == null) throw new NullPointerException("called get(null)");
        if (key.length() == 0) throw new IllegalArgumentException("invalid key");
        Node p;
        Node x = head;
        do {
            p = x;
            if (safeBitTest(key, x.b)) x = x.right;
            else x = x.left;
        } while (p.b < x.b);
        if (x.key.equals(key)) return x.val;
        else return null;
    }


void remove(String key) {
        if (key == null) throw new NullPointerException("called delete(null)");
        if (key.length() == 0) throw new IllegalArgumentException("invalid key");
        Node g;             // previous previous (grandparent)
        Node p = head;      // previous (parent)
        Node x = head;      // node to delete
        do {
            g = p;
            p = x;
            if (safeBitTest(key, x.b)) x = x.right;
            else x = x.left;
        } while (p.b < x.b);
        if (x.key.equals(key)) {
            Node z;
            Node y = head;
            do {            // find the true parent (z) of x
                z = y;
                if (safeBitTest(key, y.b)) y = y.right;
                else y = y.left;
            } while (y != x);
            if (x == p) {   // case 1: remove (leaf node) x
                Node c;     // child of x
                if (safeBitTest(key, x.b)) c = x.left;
                else c = x.right;
                if (safeBitTest(key, z.b)) z.right = c;
                else z.left = c;
            } else {          // case 2: p replaces (internal node) x
                Node c;     // child of p
                if (safeBitTest(key, p.b)) c = p.left;
                else c = p.right;
                if (safeBitTest(key, g.b)) g.right = c;
                else g.left = c;
                if (safeBitTest(key, z.b)) z.right = p;
                else z.left = p;
                p.left = x.left;
                p.right = x.right;
                p.b = x.b;
            }
            count--;
        }
    }


boolean contains(String key) {
        return get(key) != null;
    }


    boolean isEmpty() {
        return count == 0;
    }


    int size() {
        return count;
    }


std::vector<std::string> keys() {
        Queue<String> queue = new Queue<String>();
        if (head.left != head) keys(head.left, 0, queue);
        if (head.right != head) keys(head.right, 0, queue);
        return queue;
    }
private:
    Raw_node_pointer head;
    int count;

void keys(Node x, int b, Queue<String> queue) {
        if (x.b > b) {
            keys(x.left, x.b, queue);
            queue.enqueue(x.key);
            keys(x.right, x.b, queue);
        }
    }


static boolean safeBitTest(String key, int b) {
        if (b < key.length() * 16) return bitTest(key, b) != 0;
        if (b > key.length() * 16 + 15) return false;   // padding
        /* 16 bits of 0xffff */
        return true;    // end marker
    }

static int bitTest(String key, int b) {
        return (key.charAt(b >>> 4) >>> (b & 0xf)) & 1;
    }


static int safeCharAt(String key, int i) {
        if (i < key.length()) return key.charAt(i);
        if (i > key.length()) return 0x0000;            // padding
        else return 0xffff;            // end marker
    }


static int firstDifferingBit(String k1, String k2) {
        int i = 0;
        int c1 = safeCharAt(k1, 0) & ~1;
        int c2 = safeCharAt(k2, 0) & ~1;
        if (c1 == c2) {
            i = 1;
            while (safeCharAt(k1, i) == safeCharAt(k2, i)) i++;
            c1 = safeCharAt(k1, i);
            c2 = safeCharAt(k2, i);
        }
        int b = 0;
        while (((c1 >>> b) & 1) == ((c2 >>> b) & 1)) b++;
        return i * 16 + b;
    }
};

#endif // PATRICIA_ST_H
