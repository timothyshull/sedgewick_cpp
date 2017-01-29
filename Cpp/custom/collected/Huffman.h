#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <vector>

namespace Huffman {
    const static int radix = 256;

    class Node;

    using Raw_node_pointer = Node*;

    class Node {
        Node() = default;

        Node(const Node&) = default;

        Node(Node&&) = default;

        ~Node() = default

        Node& operator=(const Node&) = default;

        Node& operator=(Node&&) = default;

        Node(char ch, int freq, Raw_node_pointer left, Raw_node_pointer right);

        bool operator<(Node& rhs);

    private:
        const char _ch;
        const int _freq;
        const Raw_node_pointer _left;
        const Raw_node_pointer _right;

        bool _is_leaf();

        friend void compress();

        friend Raw_node_pointer build_trie(std::vector<int>& freq);

        friend void write_trie(Raw_node_pointer x);

        friend void build_code(std::vector<std::string>& st, Raw_node_pointer x, std::string& s);

        friend void build_code(std::vector<std::string>& st, Raw_node_pointer x, std::string&& s);

        friend void expand();

        friend Raw_node_pointer read_trie();
    };

    void compress();

    Raw_node_pointer build_trie(std::vector<int>& freq);

    void write_trie(Raw_node_pointer x);

    void build_code(std::vector<std::string>& st, Raw_node_pointer x, std::string& s);

    void build_code(std::vector<std::string>& st, Raw_node_pointer x, std::string&& s);

    void expand();

    Raw_node_pointer read_trie();
};

#endif // HUFFMAN_H
