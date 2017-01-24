#include "Symbol_digraph.h"

Symbol_digraph::Symbol_digraph(std::string& filename, std::string& delimiter)
{
    st = new ST<std::string, Integer>();

    // First pass builds the index by reading strings to associate
    // distinct strings with an index
    In in = new In(filename);
    while (in.hasNextLine()) {
        String[] a = in.read_line().split(delimiter);
        for (int i = 0; i < a.length; ++i) {
            if (!st.contains(a[i]))
                st.put(a[i], st.size());
        }
    }

    // inverted index to get string keys in an aray
    keys = new String[st.size()];
    for (String name : st.keys()) {
        keys[st.get(name)] = name;
    }

    // second pass builds the digraph by connecting first vertex on each
    // line to all others
    graph = new Digraph(st.size());
    in = new In(filename);
    while (in.hasNextLine()) {
        String[] a = in.read_line().split(delimiter);
        int v = st.get(a[0]);
        for (int i = 1; i < a.length; ++i) {
            int w = st.get(a[i]);
            graph.add_edge(v, w);
        }
    }
}

bool Symbol_digraph::contains(std::string& s)
{
    return st.contains(s);
}

int Symbol_digraph::index(std::string& s)
{
    return st.get(s);
}

int Symbol_digraph::index_of(std::string& s)
{
    return st.get(s);
}

std::string Symbol_digraph::name(int v)
{
    return keys[v];
}

std::string Symbol_digraph::nameOf(int v)
{
    return keys[v];
}

Digraph Symbol_digraph::G()
{
    return graph;
}

Digraph Symbol_digraph::digraph()
{
    return graph;
}
