#include "Flow_network.h"
#include "utility.h"
#include "Std_random.h"

Flow_network::Flow_network(int num_vertices)
        : _num_vertices{num_vertices},
          _num_edges{0},
          _adjacency_lists(static_cast<std::vector<std::vector<Flow_edge>>::size_type>(num_vertices))
{
    if (num_vertices < 0) { throw utility::Illegal_argument_exception{"Number of vertices _in a Graph must be nonnegative"}; }
    for (int v{0}; v < num_vertices; ++v) {
        _adjacency_lists[v] = std::vector<Flow_edge>{};
    }
}

Flow_network::Flow_network(int num_vertices, int num_edges)
        : _num_vertices{num_vertices},
          _num_edges{num_edges},
          _adjacency_lists(static_cast<std::vector<std::vector<Flow_edge>>::size_type>(num_vertices))
{
    if (num_vertices < 0) { throw utility::Illegal_argument_exception{"Number of vertices _in a Graph must be nonnegative"}; }
    if (num_edges < 0) { throw utility::Illegal_argument_exception{"Number of edges must be nonnegative"}; }
    int v;
    int w;
    double capacity;
    for (int i{0}; i < num_edges; ++i) {
        v = Std_random::uniform(num_vertices);
        w = Std_random::uniform(num_vertices);
        capacity = Std_random::uniform(100);
        add_edge(v, w, capacity);
    }
}

Flow_network::Flow_network(In& in) : Flow_network{in.read_int()}
{
    int num_edges{in.read_int()};
    if (num_edges < 0) { throw utility::Illegal_argument_exception{"Number of edges must be nonnegative"}; }
    int v;
    int w;
    double capacity;
    for (int i{0}; i < num_edges; ++i) {
        v = in.read_int();
        w = in.read_int();
        if (v < 0 || v >= _num_vertices) {
            std::string s{"vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(_num_vertices - 1)};
            throw utility::Index_out_of_bounds_exception{s};
        }
        if (w < 0 || w >= _num_vertices) {
            std::string s{"vertex " + std::to_string(w) + " is not between 0 and " + std::to_string(_num_vertices - 1)};
            throw utility::Index_out_of_bounds_exception{s};
        }
        capacity = in.read_double();
        add_edge(v, w, capacity);
    }
}

void Flow_network::add_edge(Flow_edge& e)
{
    int v{e.from()};
    int w{e.to()};
    _validate_vertex(v);
    _validate_vertex(w);
    _adjacency_lists[v].emplace_back(e);
    _adjacency_lists[w].emplace_back(e);
    ++_num_edges;
}

void Flow_network::add_edge(int v, int w, double capacity)
{
    _validate_vertex(v);
    _validate_vertex(w);
    _adjacency_lists[v].emplace_back(v, w, capacity);
    _adjacency_lists[w].emplace_back(v, w, capacity);
    ++_num_edges;
}

std::vector<Flow_edge> Flow_network::adjacent(int v)
{
    _validate_vertex(v);
    return _adjacency_lists[v];
}

std::vector<Flow_edge> Flow_network::edges()
{
    std::vector<Flow_edge> list;
    for (int v{0}; v < _num_vertices; ++v) {
        for (auto e : adjacent(v)) {
            if (e.to() != v) {
                list.emplace_back(e);
            }
        }
    }
    return list;
}

std::string Flow_network::to_string()
{
    std::stringstream ss;
    ss << "Flow_network(number of vertices: " << _num_vertices << ", number of edges: " << _num_edges << "\n";
    for (int v{0}; v < _num_vertices; ++v) {
        ss << "    vertex " << v + ":  ";
        for (auto e : _adjacency_lists[v]) {
            if (e.to() != v) {
                ss << e << "  ";
            }
        }
        ss << "\n";
    }
    ss << ")";
    return ss.str();
}

void Flow_network::_validate_vertex(int v)
{
    if (v < 0 || v >= _num_vertices) {
        std::string s{"vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(_num_vertices - 1)};
        throw utility::Index_out_of_bounds_exception{s};
    }
}

std::ostream& operator<<(std::ostream& os, Flow_network& out)
{
    return os << out.to_string();
}
