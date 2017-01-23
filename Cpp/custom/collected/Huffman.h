#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <vector>

namespace Huffman {
    const static int R = 256;

    class Node;

    using Raw_node_pointer = Node*;

    class Node {
    public:
        bool operator<(Node& rhs);

    private:
        const char ch;
        const int freq;
        const Raw_node_pointer left;
        const Raw_node_pointer right;

        bool isLeaf();
    };

    void compress();

    Raw_node_pointer buildTrie(std::vector<int>& freq);

    void writeTrie(Raw_node_pointer x);

    void buildCode(std::vector<std::string>& st, Raw_node_pointer x, std::string& s);

    void expand();

    Raw_node_pointer readTrie();
};

#endif // HUFFMAN_H
