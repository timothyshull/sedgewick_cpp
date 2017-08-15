// Program 17.15 - Symbol indexing for vertex names
#ifndef GRAPH_SYMBOL_TABLE_H
#define GRAPH_SYMBOL_TABLE_H

#include <string>

struct Graph_symbol_table_node;

struct Graph_symbol_table_node {
    using Raw_node_pointer = Graph_symbol_table_node*;
    using Owning_node_pointer = Graph_symbol_table_node*;

    Graph_symbol_table_node(int d) : value{-1}, data{d}, left{0}, middle{0}, right{0} {}

    ~Graph_symbol_table_node()
    {
        if (left != nullptr) { delete left; }
        if (middle != nullptr) { delete middle; }
        if (right != nullptr) { delete right; }
    }

    int value;
    int data;
    Owning_node_pointer left;
    Owning_node_pointer middle;
    Owning_node_pointer right;
};

class Graph_symbol_table {
public:
    using Raw_node_pointer = Graph_symbol_table_node*;
    using Owning_node_pointer = Graph_symbol_table_node*;

    Graph_symbol_table() : _head{nullptr}, _size(0) {}

    ~Graph_symbol_table()
    {
        if (_head != nullptr) { delete _head; }
    }

    int index(const std::string& key)
    {
        _head = _index_r(_head, key, 0);
        return _value;
    }

private:
    int _size;
    int _value;
    Owning_node_pointer _head;

    Raw_node_pointer _index_r(Raw_node_pointer node, const std::string& s, int w)
    {
        auto i = static_cast<int>(s[w]);
        if (node == nullptr) { node = new Graph_symbol_table_node{i}; }
        if (i == 0) {
            if (node->value == -1) { node->value = _size++; }
            _value = node->value;
            return node;
        }
        if (i < node->data) { node->left = _index_r(node->left, s, w); }
        if (i == node->data) { node->middle = _index_r(node->middle, s, w + 1); }
        if (i > node->data) { node->right = _index_r(node->right, s, w); }
        return node;
    }
};

#endif // GRAPH_SYMBOL_TABLE_H
