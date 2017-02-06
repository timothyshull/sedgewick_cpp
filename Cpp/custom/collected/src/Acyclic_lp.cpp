#include "Acyclic_lp.h"

Acyclic_lp::Acyclic_lp(Edge_weighted_digraph& g, int source)
        : _distance_to(static_cast<std::vector<double>::size_type>(g.num_vertices()), -std::numeric_limits<double>::infinity()),
          _edge_to(static_cast<std::vector<Directed_edge>::size_type>(g.num_vertices()))
{
    _distance_to[source] = 0.0;

    Topological topological{g};

    if (!topological.has_order()) {
        throw utility::Illegal_argument_exception{"Digraph is not acyclic."};
    }

    for (auto v : topological.order()) {
        for (auto e : g.adjacent(v)) {
            _relax(e);
        }
    }
}

Stack<Directed_edge> Acyclic_lp::path_to(int vertex)
{
    Stack<Directed_edge> path;
    if (!has_path_to(vertex)) {
        return {};
    }
    for (Directed_edge e{_edge_to[vertex]}; e != Directed_edge{}; e = _edge_to[e.from()]) {
        path.push(e);
    }
    return path;
}

void Acyclic_lp::_relax(Directed_edge& e)
{
    int v{e.from()};
    int w{e.to()};
    if (_distance_to[w] < _distance_to[v] + e.weight()) {
        _distance_to[w] = _distance_to[v] + e.weight();
        _edge_to[w] = e;
    }
}