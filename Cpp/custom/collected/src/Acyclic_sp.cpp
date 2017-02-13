#include "Acyclic_sp.h"
#include "Topological.h"

Acyclic_sp::Acyclic_sp(Edge_weighted_digraph& digraph, int source)
        : _distance_to(digraph.num_vertices(), -std::numeric_limits<double>::infinity()),
          _edge_to(digraph.num_vertices())
{
    _distance_to[source] = 0.0;

    Topological topological{digraph};
    if (!topological.has_order()) {
        throw utility::Illegal_argument_exception{"Digraph is not acyclic."};
    }
    for (auto v : topological.order()) {
        for (auto e : digraph.adjacent(v)) {
            _relax(e);
        }
    }
}

Stack<Directed_edge> Acyclic_sp::path_to(int vertex)
{
    if (!has_path_to(vertex)) { return {}; }
    Stack<Directed_edge> path;
    for (Directed_edge e{_edge_to[vertex]}; e != Directed_edge{}; e = _edge_to[e.from()]) {
        path.push(e);
    }
    return path;
}

void Acyclic_sp::_relax(Directed_edge& edge)
{
    int v{edge.from()};
    int w{edge.to()};
    if (_distance_to[w] > _distance_to[v] + edge.weight()) {
        _distance_to[w] = _distance_to[v] + edge.weight();
        _edge_to[w] = edge;
    }
}
