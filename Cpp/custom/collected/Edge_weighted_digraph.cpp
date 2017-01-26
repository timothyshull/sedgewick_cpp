#include "Edge_weighted_digraph.h"
#include "Std_in.h"
#include "Std_out.h"

Edge_weighted_digraph::Edge_weighted_digraph(int num_vertices)
        : _num_vertices{num_vertices},
          _num_edges{0},
          _adjacency_lists(static_cast<std::vector<std::vector<Directed_edge>>::size_type>(num_vertices)),
          _indegree(static_cast<std::vector<int>::size_type>(num_vertices))
{
    if (num_vertices < 0) {
        throw utility::Illegal_argument_exception("the number of vertices _in an Edge_weighted_digraph must be non-negative");
    }
    for (int v{0}; v < _num_vertices; ++v) {
        _adjacency_lists[v] = std::vector<Directed_edge>{};
    }
}

Edge_weighted_digraph::Edge_weighted_digraph(int num_vertices, int num_edges)
        : _num_vertices{num_vertices},
          _num_edges{num_edges},
          _adjacency_lists(static_cast<std::vector<std::vector<Directed_edge>>::size_type>(num_vertices)),
          _indegree(static_cast<std::vector<int>::size_type>(num_vertices))
{
    int v;
    int w;
    double weight;
    for (int i{0}; i < _num_edges; ++i) {
        v = Std_random::uniform(_num_vertices);
        w = Std_random::uniform(_num_vertices);
        weight = 0.01 * Std_random::uniform(100);
        add_edge(v, w, weight);
    }
}

Edge_weighted_digraph::Edge_weighted_digraph(std::istream& in)
{
    utility::copy_stream(in, Std_in::std_in);
    int num_vertices = Std_in::read_int();
    *this = Edge_weighted_digraph{num_vertices};
    int num_edges = Std_in::read_int();
    _num_edges = num_edges;
    if (_num_edges < 0) {
        throw utility::Index_out_of_bounds_exception("The number of edges must be non-negative");
    }

    int v;
    int w;
    double weight;
    for (int i{0}; i < num_edges; ++i) {
        Std_out::print_line("add edge");
        v = Std_in::read_int();
        w = Std_in::read_int();
        if (v < 0 || v >= num_vertices || w < 0 || w >= num_vertices) {
            throw utility::Index_out_of_bounds_exception("The vertex must be between 0 and the number of vertices - 1");
        }
        weight = Std_in::read_double();
        add_edge(v, w, weight);
    }
    // reset
    utility::copy_stream(std::cin, Std_in::std_in);
}

Edge_weighted_digraph::Edge_weighted_digraph(const Edge_weighted_digraph& g)
        : _num_vertices{g._num_vertices},
          _num_edges{g._num_edges},
          _indegree{g._indegree}
{
    for (int v{0}; v < _num_vertices; ++v) {
        Stack<Directed_edge> reverse;
        for (auto e : g._adjacency_lists[v]) {
            reverse.push(e);
        }
        for (auto e : reverse) {
            _adjacency_lists[v].emplace_back(e);
        }
    }
}

void Edge_weighted_digraph::add_edge(Directed_edge& e)
{
    int v = e.from();
    int w = e.to();
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

std::vector<Directed_edge> Edge_weighted_digraph::adjacent(int v) const
{
    _validate_vertex(v);
    return _adjacency_lists[v];
}

int Edge_weighted_digraph::outdegree(int v) const
{
    _validate_vertex(v);
    return static_cast<int>(_adjacency_lists[v].size());
}

int Edge_weighted_digraph::indegree(int v) const
{
    _validate_vertex(v);
    return _indegree[v];
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
    ss << "Edge_weighted_digraph(\n    number of vertices: " << _num_vertices << ",\n    number of edges: " << _num_edges << "\n";
    for (int v{0}; v < _num_vertices; ++v) {
        ss << "    edges for vertex " << v << ": ";
        for (auto e : _adjacency_lists[v]) {
            ss << e << " ";
        }
        ss << "\n";
    }
    ss << ")\n";
    return ss.str();
}

void Edge_weighted_digraph::_validate_vertex(int v) const
{
    if (v < 0 || v >= _num_vertices) {
        throw utility::Index_out_of_bounds_exception("The vertex is not between 0 and the number of vertices");
    }
}

std::ostream& operator<<(std::ostream& os, const Edge_weighted_digraph& out)
{
    return os << out.to_string();
}