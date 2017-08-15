#include "Edge_weighted_digraph.h"
#include "Std_in.h"
#include "Std_out.h"

Edge_weighted_digraph::Edge_weighted_digraph(std::size_t num_vertices)
        : _num_vertices{num_vertices},
          _num_edges{0},
          _adjacency_lists(static_cast<std::vector<std::vector<Directed_edge>>::size_type>(num_vertices), std::vector<Directed_edge>{}),
          _indegree(static_cast<std::vector<int>::size_type>(num_vertices)) {}

Edge_weighted_digraph::Edge_weighted_digraph(std::size_t num_vertices, std::size_t num_edges)
        : _num_vertices{num_vertices},
          _num_edges{num_edges},
          _adjacency_lists(static_cast<std::vector<std::vector<Directed_edge>>::size_type>(num_vertices)),
          _indegree(static_cast<std::vector<int>::size_type>(num_vertices))
{
    for (auto i = 0; i < _num_edges; ++i) {
        auto v = Std_random::uniform(static_cast<int>(_num_vertices));
        auto w = Std_random::uniform(static_cast<int>(_num_vertices));
        auto weight = 0.01 * Std_random::uniform(100);
        add_edge(v, w, weight);
    }
}

Edge_weighted_digraph::Edge_weighted_digraph(In<std::ifstream>& in)
        : Edge_weighted_digraph{static_cast<std::size_t>(in.read_int())}
{
    auto num_edges = in.read_int();
    if (num_edges < 0) { throw utility::Index_out_of_bounds_exception("The number of edges must be non-negative"); }

    for (auto i = 0; i < num_edges; ++i) {
        auto v = in.read_int();
        auto w = in.read_int();
        if (v < 0 || v >= _num_vertices || w < 0 || w >= _num_vertices) {
            throw utility::Index_out_of_bounds_exception("The vertex must be between 0 and the number of vertices - 1");
        }
        auto weight = in.read_double();
        add_edge(v, w, weight);
    }
}

Edge_weighted_digraph::Edge_weighted_digraph(const Edge_weighted_digraph& digraph)
        : _num_vertices{digraph._num_vertices},
          _num_edges{digraph._num_edges},
          _indegree{digraph._indegree}
{
    for (auto v = 0; v < _num_vertices; ++v) {
        Stack<Directed_edge> reverse;
        for (auto e : digraph._adjacency_lists[v]) { reverse.push(e); }
        for (auto e : reverse) { _adjacency_lists[v].emplace_back(e); }
    }
}

void Edge_weighted_digraph::add_edge(Directed_edge& e)
{
    auto v = e.from();
    auto w = e.to();
    _validate_vertex(v);
    _validate_vertex(w);
    _adjacency_lists[v].emplace_back(e);
    _indegree[w] += 1;
    ++_num_edges;
}

void Edge_weighted_digraph::add_edge(int source, int destination, double weight)
{
    _validate_vertex(source);
    _validate_vertex(destination);
    _adjacency_lists[source].emplace_back(source, destination, weight);
    _indegree[destination] += 1;
    ++_num_edges;
}

std::vector<Directed_edge> Edge_weighted_digraph::adjacent(int vertex) const
{
    _validate_vertex(vertex);
    return _adjacency_lists[vertex];
}

int Edge_weighted_digraph::outdegree(int vertex) const
{
    _validate_vertex(vertex);
    return static_cast<int>(_adjacency_lists[vertex].size());
}

int Edge_weighted_digraph::indegree(int vertex) const
{
    _validate_vertex(vertex);
    return _indegree[vertex];
}

std::vector<Directed_edge> Edge_weighted_digraph::edges() const
{
    std::vector<Directed_edge> list;
    for (auto v : _adjacency_lists) {
        for (auto e : v) {
            list.emplace_back(e);
        }
    }
    return list;
}

std::string Edge_weighted_digraph::to_string() const
{
    std::stringstream ss;
    ss << "Edge_weighted_digraph(number of vertices: " << _num_vertices << ", number of edges: " << _num_edges << "\n";
    for (auto v = 0; v < _num_vertices; ++v) {
        ss << "    vertex " << v << ": ";
        for (auto e : _adjacency_lists[v]) {
            ss << e << " ";
        }
        ss << "\n";
    }
    ss << ")\n";
    return ss.str();
}

void Edge_weighted_digraph::_validate_vertex(int vertex) const
{
    if (vertex < 0 || vertex >= _num_vertices) {
        throw utility::Index_out_of_bounds_exception("The vertex is not between 0 and the number of vertices");
    }
}

