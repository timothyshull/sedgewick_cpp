#ifndef SYMBOL_GRAPH_H
#define SYMBOL_GRAPH_H

#include <string>
#include <map>
#include "Graph.h"
#include "Symbol_table.h"

class Symbol_graph {
public:
    Symbol_graph(std::string& filename, const char delimiter);

    inline bool contains(std::string& s) const { return _st.contains(s); }

    inline bool contains(std::string&& s) const { return _st.contains(s); }

    inline int index(std::string& s) const { return _st.get(s); }

    inline int index(std::string&& s) const { return _st.get(s); }

    inline int index_of(std::string& s) const { return _st.get(s); }

    inline int index_of(std::string&& s) const { return _st.get(s); }

    inline std::string name(int v) const { return _keys[v]; }

    inline std::string name_of(int v) const { return _keys[v]; }

    inline Graph graph() const { return _graph; }

    inline Graph digraph() const { return _graph; }

private:
    Symbol_table<std::string, int> _st;
    std::vector<std::string> _keys;
    Graph _graph;
};

#endif // SYMBOL_GRAPH_H
