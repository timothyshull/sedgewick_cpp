#ifndef SYMBOL_GRAPH_H
#define SYMBOL_GRAPH_H

#include <string>
#include <map>
#include "Graph.h"

class Symbol_graph {
public:
    Symbol_graph(std::string& filename, std::string& delimiter);

    bool contains(std::string& s);

    int index(std::string& s);

    int indexOf(std::string& s);

    std::string name(int v);

    std::string nameOf(int v);

    Graph G();

    Graph digraph();

private:
    std::map<std::string, int> st;
    std::vector<std::string> keys;
    Graph graph;
};

#endif // SYMBOL_GRAPH_H
