#ifndef SYMBOL_DIGRAPH_H
#define SYMBOL_DIGRAPH_H

#include <map>
#include "Digraph.h"

class Symbol_digraph {
public:
    Symbol_digraph(std::string& filename, std::string& delimiter);

    bool contains(std::string& s);

    int index(std::string& s);

    int indexOf(std::string& s);

    std::string name(int v);

    std::string nameOf(int v);

    Digraph G();

    Digraph digraph();

private:
    std::map<std::string, int> st;
    std::vector<std::string> keys;
    Digraph graph;

};

#endif // SYMBOL_DIGRAPH_H
