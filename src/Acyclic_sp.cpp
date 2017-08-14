#include "Acyclic_sp.h"
#include "Topological.h"

Acyclic_sp::Acyclic_sp(Edge_weighted_digraph &digraph, int source)
        : _distance_to(digraph.num_vertices(), -std::numeric_limits<double>::infinity()),
          _edge_to(digraph.num_vertices())
{
    _distance_to[source] = 0.0;
    auto topological = Topological{digraph};
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
    if (!has_path_to(vertex)) {
        return {};
    }
    auto path = Stack<Directed_edge>{};
    for (auto e = _edge_to[vertex]; e != _default(); e = _edge_to[e.from()]) {
        path.push(e);
    }
    return path;
}

void Acyclic_sp::_relax(Directed_edge const &edge)
{
    auto v = edge.from();
    auto w = edge.to();
    if (_distance_to[w] > _distance_to[v] + edge.weight()) {
        _distance_to[w] = _distance_to[v] + edge.weight();
        _edge_to[w] = edge;
    }
}
