#include "Edge_weighted_graph.h"
#include "utility.h"
#include "Std_random.h"
#include "Stack.h"

Edge_weighted_graph::Edge_weighted_graph(int num_vertices)
        : _num_vertices{num_vertices},
          _num_edges{0},
          _adjacency_lists(static_cast<std::vector<std::vector<Edge>>::size_type>(num_vertices))
{
    if (num_vertices < 0) { throw utility::Illegal_argument_exception{"Number of vertices must be nonnegative"}; }
    for (auto v = 0; v < num_vertices; ++v) {
        _adjacency_lists[v] = std::vector<Edge>{};
    }
}

Edge_weighted_graph::Edge_weighted_graph(int num_vertices, int num_edges) : Edge_weighted_graph{num_vertices}
{
    if (num_edges < 0) { throw utility::Illegal_argument_exception{"Number of edges must be nonnegative"}; }
    int v;
    int w;
    double weight;
    for (auto i = 0; i < num_edges; ++i) {
        v = Std_random::uniform(num_vertices);
        w = Std_random::uniform(num_vertices);
        weight = std::round(100 * Std_random::uniform()) / 100.0;
        add_edge(v, w, weight);
    }
}

Edge_weighted_graph::Edge_weighted_graph(In& in) : Edge_weighted_graph{in.read_int()}
{
    auto num_edges = in.read_int();
    if (num_edges < 0) { throw utility::Illegal_argument_exception{"Number of edges must be nonnegative"}; }
    int v;
    int w;
    double weight;
    for (auto i = 0; i < num_edges; ++i) {
        v = in.read_int();
        w = in.read_int();
        weight = in.read_double();
        add_edge(v, w, weight);
    }
}

Edge_weighted_graph::Edge_weighted_graph(Edge_weighted_graph& graph)
        : Edge_weighted_graph{graph.num_vertices()},
          _num_edges{graph.num_edges()}
{
    for (auto v = 0; v < graph.num_vertices(); ++v) {
        Stack<Edge> reverse;
        for (auto e : graph._adjacency_lists[v]) {
            reverse.push(e);
        }
        for (auto e : reverse) {
            _adjacency_lists[v].emplace_back(e);
        }
    }
}

void Edge_weighted_graph::add_edge(Edge& edge)
{
    int v = edge.either();
    int w = edge.other(v);
    _validate_vertex(v);
    _validate_vertex(w);
    _adjacency_lists[v].emplace_back(edge);
    _adjacency_lists[w].emplace_back(edge);
    ++_num_edges;
}

std::vector<Edge> Edge_weighted_graph::adjacent(int vertex)
{
    _validate_vertex(vertex);
    return _adjacency_lists[vertex];
}

int Edge_weighted_graph::degree(int v)
{
    _validate_vertex(v);
    return static_cast<int>(_adjacency_lists[v].size());
}

std::vector<Edge> Edge_weighted_graph::edges()
{
    std::vector<Edge> list;
    int self_loops;
    for (auto v = 0; v < _num_vertices; ++v) {
        self_loops = 0;
        for (auto e : adjacent(v)) {
            if (e.other(v) > v) {
                list.emplace_back(e);
            } else if (e.other(v) == v) {
                if (self_loops % 2 == 0) { list.emplace_back(e); }
                ++self_loops;
            }
        }
    }
    return list;
}

std::string Edge_weighted_graph::to_string()
{
    std::stringstream ss;
    ss << "Edge_weighted_graph(number of vertices: " << _num_vertices + ", number of edges: " << _num_edges << "\n";
    for (auto v = 0; v < _num_vertices; ++v) {
        ss << "vertex " << v << ": ";
        for (auto e : _adjacency_lists[v]) {
            ss << e << "  ";
        }
        ss << "\n";
    }
    return ss.str();
}

void Edge_weighted_graph::_validate_vertex(int vertex)
{
    if (vertex < 0 || vertex >= _num_vertices) {
        std::string s{"vertex " + std::to_string(vertex) + " is not between 0 and " + std::to_string(_num_vertices - 1)};
        throw utility::Index_out_of_bounds_exception{s};
    }
}

std::ostream& operator<<(std::ostream& os, Edge_weighted_graph& out)
{
    return os << out.to_string();
}
