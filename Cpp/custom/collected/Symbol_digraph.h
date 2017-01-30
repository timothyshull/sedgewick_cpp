#ifndef SYMBOL_DIGRAPH_H
#define SYMBOL_DIGRAPH_H

#include <map>
#include "Digraph.h"
#include "Symbol_table.h"

class Symbol_digraph {
public:
    Symbol_digraph(std::string& filename, const char delimiter);

    inline bool contains(std::string& s) const { return _st.contains(s); }

    inline bool contains(std::string&& s) const { return _st.contains(s); }

    inline int index(std::string& s) { return _st.get(s); }

    inline int index(std::string&& s) { return _st.get(s); }

    inline int index_of(std::string& s) { return _st.get(s); }

    inline int index_of(std::string&& s) { return _st.get(s); }

    inline std::string name(int v) const { return _keys[v]; }

    inline std::string name_of(int v) const { return _keys[v]; }

    inline Digraph graph() const { return _graph; }

    inline Digraph digraph() const { return _graph; }

private:
    Symbol_table<std::string, int> _st;
    std::vector<std::string> _keys;
    Digraph _graph;

};

#endif // SYMBOL_DIGRAPH_H
