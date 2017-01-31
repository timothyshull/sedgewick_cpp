#include "Acyclic_sp.h"
#include "Edge_weighted_digraph.h"
#include "Stack.h"
#include "Topological.h"

Acyclic_sp::Acyclic_sp(Edge_weighted_digraph& digraph, int source)
        : _distance_to(static_cast<std::vector<double>::size_type>(digraph.num_vertices()), std::numeric_limits<double>::infinity()),
          _edge_to(static_cast<std::vector<Directed_edge>::size_type>(digraph.num_vertices()))
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

std::vector<Directed_edge> Acyclic_sp::path_to(int vertex)
{
    if (!has_path_to(vertex)) { return {}; }
    std::vector<Directed_edge> path{};
    for (Directed_edge e{_edge_to[vertex]}; e != null; e = _edge_to[e.from()]) {
        path.emplace_back(e);
    }
    return path;
}

void Acyclic_sp::_relax(Directed_edge& e)
{
    int v = e.from(), w = e.to();
    if (_distance_to[w] > _distance_to[v] + e.weight()) {
        _distance_to[w] = _distance_to[v] + e.weight();
        _edge_to[w] = e;
    }
}
