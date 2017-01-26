#include "Symbol_graph.h"

Symbol_graph::Symbol_graph(std::string& filename, std::string& delimiter)
{
    st = new ST<std::string, Integer>();

    // First pass builds the index by reading strings to associate
    // distinct strings with an index
    In in = new In(filename);
    // while (_in.hasNextLine()) {
    while (!in.is_empty()) {
        std::vector<std::string> a = in.read_line().split(delimiter);
        for (int i{0}; i < a.length; ++i) {
            if (!st.contains(a[i]))
                st.put(a[i], st.size());
        }
    }
    Std_out::print_line("Done reading " + filename);

    // inverted index to get string keys _in an aray
    keys = new String[st.size()];
    for (String name : st.keys()) {
        keys[st.get(name)] = name;
    }

    // second pass builds the graph by connecting first vertex on each
    // line to all others
    graph = new Graph(st.size());
    in = new In(filename);
    while (in.hasNextLine()) {
        std::vector<std::string> a = in.read_line().split(delimiter);
        int v = st.get(a[0]);
        for (int i{1}; i < a.length; ++i) {
            int w = st.get(a[i]);
            graph.add_edge(v, w);
        }
    }
}

bool Symbol_graph::contains(std::string& s)
{
    return st.contains(s)
}

int Symbol_graph::index(std::string& s)
{
    return st.get(s);
}

int Symbol_graph::index_of(std::string& s)
{
    return st.get(s);
}

std::string Symbol_graph::name(int v)
{
    return keys[v];
}

std::string Symbol_graph::nameOf(int v)
{
    return keys[v];
}

Graph Symbol_graph::G()
{
    return graph;
}

Graph Symbol_graph::digraph()
{
    return graph;
}
