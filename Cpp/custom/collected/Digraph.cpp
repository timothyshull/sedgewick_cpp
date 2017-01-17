#include <sstream>

#include "Digraph.h"
#include "Std_in.h"
#include "utility.h"
#include "Stack.h"

// do not need the negative size check here because the vector ctors will throw
Digraph::Digraph(int num_vertices) : _num_vertices{num_vertices}, _num_edges{0}, _indegree(num_vertices), _adjacency_lists(num_vertices) {}

Digraph::Digraph(std::istream in)
{
    // TODO: handle No_such_element_exception
    Std_in::std_in = in;
    _num_vertices = Std_in::read_int();
    if (_num_vertices < 0) {
        throw utility::Illegal_argument_exception("The number of vertices in a Digraph must be non-negative");
    }
    _indegree = std::vector<int>(_num_vertices);
    _adjacency_lists = std::vector<Bag<int>>(_num_vertices);

    _num_edges = Std_in::read_int();
    if (_num_edges < 0) {
        throw utility::Illegal_argument_exception("The number of edges in a Digraph must be non-negative");
    }

    int v;
    int w;
    for (int i = 0; i < _num_edges; ++i) {
        v = Std_in::read_int();
        w = Std_in::read_int();
        add_edge(v, w);
    }
    // reset
    Std_in::std_in = std::cin;
}

Digraph::Digraph(Digraph& g) : _num_vertices{g._num_vertices}, _num_edges{g._num_edges}, _indegree{g._indegree}, _adjacency_lists(g._num_vertices)
{
    for (int v = 0; v < g._num_vertices; ++v) {
        Stack<int> reverse;
        for (int w : g._adjacency_lists[v]) {
            reverse.push(w);
        }
        for (int w : reverse) {
            _adjacency_lists[v].add(w);
        }
    }
}

int Digraph::num_vertices() const
{
    return _num_vertices;
}

int Digraph::num_edges() const
{
    return _num_edges;
}

void Digraph::add_edge(int v, int w)
{
    _validate_vertex(v);
    _validate_vertex(w);
    _adjacency_lists[v].add(w);
    _indegree[w] += 1;
    ++_num_edges;
}

Bag<int> Digraph::adjacent(int v) const
{
    _validate_vertex(v);
    return _adjacency_lists[v];
}

int Digraph::outdegree(int v) const
{
    _validate_vertex(v);
    return _adjacency_lists[v].size();
}

int Digraph::indegree(int v) const
{
    _validate_vertex(v);
    return _indegree[v];
}

Digraph Digraph::reverse() const
{
    Digraph reverse(_num_vertices);
    for (int v = 0; v < _num_vertices; ++v) {
        for (auto w : adjacent(v)) {
            reverse.add_edge(w, v);
        }
    }
    return reverse;
}

std::string Digraph::to_string() const
{
    std::stringstream ss;
    ss << "Digraph(number of vertices: " << _num_vertices << ", number of edges: " << _num_edges << "\n";
    for (int v = 0; v < _num_vertices; ++v) {
        ss << "    Vertex " << v << ": ";
        for (auto w : _adjacency_lists[v]) {
            ss << w << ", ";
        }
        ss << "\n";
    }
    ss << ")\n";
    return ss.str();
}

void Digraph::_validate_vertex(int v) const
{
    if (v < 0 || v >= _num_vertices) {
        std::stringstream ss;
        ss << "Vertex " << v << " is not between 0 and " << _num_vertices;
        throw utility::Index_out_of_bounds_exception(ss.str());
    }

}

std::ostream& operator<<(std::ostream& os, const Digraph& out)
{
    return os << out.to_string();
}