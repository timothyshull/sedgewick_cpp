#include "Acyclic_lp.h"

Acyclic_lp::Acyclic_lp(Edge_weighted_digraph &g, int source)
        : _distance_to(g.num_vertices(), -std::numeric_limits<double>::infinity()),
          _edge_to(g.num_vertices())
{
    _distance_to[source] = 0.0;

    auto topological = Topological{g};
    if (!topological.has_order()) { throw utility::Illegal_argument_exception{"Digraph is not acyclic."}; }
    for (auto v : topological.order()) {
        for (auto const &e : g.adjacent(v)) {
            _relax(e);
        }
    }
}

Stack<Directed_edge> Acyclic_lp::path_to(int vertex)
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

void Acyclic_lp::_relax(Directed_edge const &e)
{
    auto v = e.from();
    auto w = e.to();
    if (_distance_to[w] < _distance_to[v] + e.weight()) {
        _distance_to[w] = _distance_to[v] + e.weight();
        _edge_to[w] = e;
    }
}