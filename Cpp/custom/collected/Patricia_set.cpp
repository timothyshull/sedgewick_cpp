#include "Patricia_set.h"

Patricia_set_node::Patricia_set_node(std::string& key, int b) : key{key}, b{b} {}

Patricia_set::Patricia_set() : count{0}
{
    head = new Patricia_set_node{"", 0};
    head->left = head;
    head->right = head;
}

void Patricia_set::add(std::string& key)
{
    if (key == null) throw new NullPointerException("called add(null)");
    if (key.length() == 0) throw new IllegalArgumentException("invalid key");
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
        Node t = new Node(key, b);
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
    }
}

bool Patricia_set::contains(std::string& key)
{
    if (key == null) throw new NullPointerException("called contains(null)");
    if (key.length() == 0) throw new IllegalArgumentException("invalid key");
    Node p;
    Node x = head;
    do {
        p = x;
        if (safeBitTest(key, x.b)) x = x.right;
        else x = x.left;
    } while (p.b < x.b);
    return x.key.equals(key);
}

void Patricia_set::remove(std::string& key)
{
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
    std::stringstream s = new std::stringstream();
    for (String key : this) s.append(key + " ");
    if (s.length() > 0) s.deleteCharAt(s.length() - 1);
    return s.to_string();
}

void Patricia_set::collect(Patricia_set::Raw_node_pointer x, int b, Queue<std::string> queue)
{
    if (x.b > b) {
        collect(x.left, x.b, queue);
        queue.enqueue(x.key);
        collect(x.right, x.b, queue);
    }
}

bool Patricia_set::safeBitTest(std::string& key, int b)
{
    if (b < key.length() * 16) return bitTest(key, b) != 0;
    if (b > key.length() * 16 + 15) return false;   // padding
    /* 16 bits of 0xffff */
    return true;
}

int Patricia_set::bitTest(std::string& key, int b)
{
    return (key.charAt(b >> 4) >> (b & 0xf)) & 1;
}

int Patricia_set::safeCharAt(std::string& key, int i)
{
    if (i < key.length()) return key.charAt(i);
    if (i > key.length()) return 0x0000;            // padding
    else return 0xffff;
}

int Patricia_set::firstDifferingBit(std::string& k1, std::string& k2)
{
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
    while (((c1 >> b) & 1) == ((c2 >> b) & 1)) b++;
    return i * 16 + b;
}
