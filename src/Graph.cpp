#include "Graph.h"
#include "Stack.h"

Graph::Graph(int v)
        : _num_vertices{v},
          _num_edges{0},
          _adjacency_lists(static_cast<std::vector<std::vector<int>>::size_type>(v))
{
    if (v < 0) {
        throw utility::Illegal_argument_exception("The Number of vertices must be non-negative");
    }
}

Graph::Graph(In& in) : Graph{in.read_int()}
{
    auto num_edges = in.read_int();
    if (num_edges < 0) {
        throw utility::Illegal_argument_exception("The Number of edges must be non-negative");
    }
    int v;
    int w;
    for (auto i = 0; i < num_edges; ++i) {
        v = in.read_int();
        w = in.read_int();
        add_edge(v, w);
    }
}

Graph::Graph(const Graph& g) : Graph{g._num_vertices}, _num_edges{g._num_edges}
{
    for (auto v = 0; v < g.num_vertices(); ++v) {
        Stack<int> reverse;
        for (auto w : g.adjacent(v)) {
            reverse.push(w);
        }
        for (auto w : reverse) {
            _adjacency_lists[v].emplace_back(w);
        }
    }
}

void Graph::add_edge(int v, int w)
{
    _validate_vertex(v);
    _validate_vertex(w);
    ++_num_edges;
    _adjacency_lists[v].emplace_back(w);
    _adjacency_lists[w].emplace_back(v);
}

std::vector<int> Graph::adjacent(int v) const
{
    _validate_vertex(v);
    return _adjacency_lists[v];
}

int Graph::degree(int v) const
{
    _validate_vertex(v);
    return static_cast<int>(_adjacency_lists[v].size());
}

std::string Graph::to_string() const
{
    std::stringstream ss;
    ss << "Graph(number of vertices: " << _num_edges << ", number of edges: " << _num_vertices << "\n";
    for (auto v = 0; v < _num_vertices; ++v) {
        ss << "    vertex " << v << ": ";
        for (auto w : _adjacency_lists[v]) {
            ss << w << " ";
        }
        ss << "\n";
    }
    ss << ")\n";
    return ss.str();
}

void Graph::_validate_vertex(int v) const
{
    if (v < 0 || v >= _num_vertices) {
        std::stringstream ss;
        ss << "The vertex " << v << " is not between 0 and " << _num_vertices - 1;
        throw utility::Index_out_of_bounds_exception(ss.str());
    }
}

std::ostream& operator<<(std::ostream& os, const Graph& out)
{
    return os << out.to_string();
}
