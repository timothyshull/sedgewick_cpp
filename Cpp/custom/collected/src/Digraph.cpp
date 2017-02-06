#include <sstream>

#include "Digraph.h"
#include "Std_in.h"
#include "utility.h"
#include "Stack.h"

// do not need the negative size _check here because the vector ctors will throw
Digraph::Digraph(int num_vertices) : _num_vertices{num_vertices}, _num_edges{0}, _indegree(num_vertices), _adjacency_lists(num_vertices) {}

Digraph::Digraph(std::istream in)
{
    utility::copy_stream(in, Std_in::std_in);
    _num_vertices = Std_in::read_int();
    if (_num_vertices < 0) {
        throw utility::Illegal_argument_exception("The number of vertices _in a Digraph must be non-negative");
    }
    _indegree.reserve(static_cast<std::vector<int>::size_type>(_num_vertices));
    _adjacency_lists.reserve(static_cast<std::vector<int>::size_type>(_num_vertices));

    _num_edges = Std_in::read_int();
    if (_num_edges < 0) {
        throw utility::Illegal_argument_exception("The number of edges _in a Digraph must be non-negative");
    }

    int v;
    int w;
    for (int i{0}; i < _num_edges; ++i) {
        v = Std_in::read_int();
        w = Std_in::read_int();
        add_edge(v, w);
    }
    // reset
    utility::copy_stream(std::cin, Std_in::std_in);
}

Digraph::Digraph(Digraph& g) : _num_vertices{g._num_vertices}, _num_edges{g._num_edges}, _indegree{g._indegree}, _adjacency_lists(g._num_vertices)
{
    for (int v{0}; v < g._num_vertices; ++v) {
        Stack<int> reverse;
        for (int w : g._adjacency_lists[v]) {
            reverse.push(w);
        }
        for (int w : reverse) {
            _adjacency_lists[v].emplace_back(w);
        }
    }
}

void Digraph::add_edge(int v, int w)
{
    _validate_vertex(v);
    _validate_vertex(w);
    _adjacency_lists[v].emplace_back(w);
    _indegree[w] += 1;
    ++_num_edges;
}

std::vector<int> Digraph::adjacent(int v) const
{
    _validate_vertex(v);
    return _adjacency_lists[v];
}

int Digraph::outdegree(int v) const
{
    _validate_vertex(v);
    return static_cast<int>(_adjacency_lists[v].size());
}

int Digraph::indegree(int v) const
{
    _validate_vertex(v);
    return _indegree[v];
}

Digraph Digraph::reverse() const
{
    Digraph reverse{_num_vertices};
    for (int v{0}; v < _num_vertices; ++v) {
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
    for (int v{0}; v < _num_vertices; ++v) {
        ss << "    vertex " << v << ": ";
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