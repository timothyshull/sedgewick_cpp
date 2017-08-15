#include <sstream>

#include "Digraph.h"
#include "Std_in.h"
#include "Stack.h"

Digraph::Digraph(std::size_t num_vertices)
        : _num_vertices{num_vertices},
          _num_edges{0},
          _indegree(num_vertices),
          _adjacency_lists(num_vertices) {}

Digraph::Digraph(In<std::ifstream>& in)
{
    _num_vertices = static_cast<std::size_t>(in.read_int());
    _indegree.reserve(static_cast<std::vector<int>::size_type>(_num_vertices));
    _adjacency_lists.reserve(static_cast<std::vector<int>::size_type>(_num_vertices));
    _num_edges = static_cast<std::size_t>(in.read_int());

    for (auto i = 0; i < _num_edges; ++i) {
        auto v = in.read_int();
        auto w = in.read_int();
        add_edge(v, w);
    }
}

Digraph::Digraph(Digraph& digraph) : _num_vertices{digraph._num_vertices}, _num_edges{digraph._num_edges}, _indegree{digraph._indegree}, _adjacency_lists(digraph._num_vertices)
{
    for (auto v = 0; v < digraph._num_vertices; ++v) {
        Stack<int> reverse;
        for (auto w : digraph._adjacency_lists[v]) { reverse.push(w); }
        for (auto w : reverse) { _adjacency_lists[v].emplace_back(w); }
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
    for (auto v = 0; v < _num_vertices; ++v) {
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
    for (auto v = 0; v < _num_vertices; ++v) {
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
