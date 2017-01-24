#include "Trie_set.h"

Trie_set::Trie_set() : root{nullptr}, n{0} {}

bool Trie_set::contains(std::string& key)
{
    Node x = get(root, key, 0);
    if (x == null) return false;
    return x.isString;
}

void Trie_set::add(std::string& key)
{
    root = add(root, key, 0);
}

int Trie_set::size()
{
    return n;
}

bool Trie_set::is_empty()
{
    return size() == 0;
}

std::vector<std::string> Trie_set::iterator()
{
    return keysWithPrefix("").iterator();
}

std::vector<std::string> Trie_set::keysWithPrefix()
{
    Queue<std::string> results = new Queue<std::string>();
    Node x = get(root, prefix, 0);
    collect(x, new std::stringstream(prefix), results);
    return results;
}

std::vector<std::string> Trie_set::keysThatMatch()
{
    Queue<std::string> results = new Queue<std::string>();
    std::stringstream prefix = new std::stringstream();
    collect(root, prefix, pattern, results);
    return results;
}

std::string Trie_set::longestPrefixOf(std::string& query)
{
    int length = longestPrefixOf(root, query, 0, -1);
    if (length == -1) return null;
    return query.substring(0, length);
}

void Trie_set::remove(std::string& key)
{
    root = delete(root, key, 0);
}

Trie_set::Raw_node_pointer Trie_set::get(Trie_set::Raw_node_pointer x, std::string& key, int d)
{
    if (x == null) return null;
    if (d == key.length()) return x;
    char c = key.charAt(d);
    return get(x.next[c], key, d + 1);
}

Trie_set::Raw_node_pointer Trie_set::add(Trie_set::Raw_node_pointer x, std::string& key, int d)
{
    if (x == null) x = new Node();
    if (d == key.length()) {
        if (!x.isString) n++;
        x.isString = true;
    } else {
        char c = key.charAt(d);
        x.next[c] = add(x.next[c], key, d + 1);
    }
    return x;
}

void Trie_set::collect(Trie_set::Raw_node_pointer x, std::stringstream& prefix, Queue<std::string>& results)
{
    if (x == null) return;
    if (x.isString) results.enqueue(prefix.to_string());
    for (char c = 0; c < R; ++c) {
        prefix.append(c);
        collect(x.next[c], prefix, results);
        prefix.deleteCharAt(prefix.length() - 1);
    }
}

void Trie_set::collect(Trie_set::Raw_node_pointer x, std::stringstream& pattern, Queue<std::string>& results, void)
{
    if (x == null) return;
    int d = prefix.length();
    if (d == pattern.length() && x.isString)
        results.enqueue(prefix.to_string());
    if (d == pattern.length())
        return;
    char c = pattern.charAt(d);
    if (c == '.') {
        for (char ch = 0; ch < R; ++ch) {
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

int Trie_set::longestPrefixOf(Trie_set::Raw_node_pointer x, std::string& query, int d, int length)
{
    if (x == null) return length;
    if (x.isString) length = d;
    if (d == query.length()) return length;
    char c = query.charAt(d);
    return longestPrefixOf(x.next[c], query, d + 1, length);
}

Trie_set::Raw_node_pointer Trie_set::remove(Trie_set::Raw_node_pointer x, std::string& key, int d)
{
    if (x == null) return null;
    if (d == key.length()) {
        if (x.isString) n--;
        x.isString = false;
    } else {
        char c = key.charAt(d);
        x.next[c] = delete(x.next[c], key, d + 1);
    }

    // remove subtrie rooted at x if it is completely empty
    if (x.isString) return x;
    for (int c = 0; c < R; ++c)
        if (x.next[c] != null)
            return x;
    return null;
}
