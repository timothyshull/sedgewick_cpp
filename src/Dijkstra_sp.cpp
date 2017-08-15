#include "Dijkstra_sp.h"

Dijkstra_sp::Dijkstra_sp(Edge_weighted_digraph& digraph, int source)
        : _distance_to(static_cast<std::vector<double>::size_type>(digraph.num_vertices())),
          _edge_to(static_cast<std::vector<Directed_edge>::size_type>(digraph.num_vertices())),
          _pq{digraph.num_vertices()}
{
    for (auto e : digraph.edges()) {
        if (e.weight() < 0) {
            throw utility::Illegal_argument_exception("edge " + e.to_string() + " has negative weight");
        }
    }

    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        _distance_to[v] = std::numeric_limits<double>::infinity();
    }
    _distance_to[source] = 0.0;

    _pq.insert(source, _distance_to[source]);
    int v;
    while (!_pq.is_empty()) {
        v = _pq.delMin();
        for (auto e : digraph.adjacent(v)) {
            _relax(e);
        }
    }

    utility::alg_assert(_check(digraph, source), "The Dijkstra_sp invariant check failed after construction");
}

Stack<Directed_edge> Dijkstra_sp::path_to(int vertex)
{
    if (!has_path_to(vertex)) { return {}; }
    Stack<Directed_edge> path;
    for (Directed_edge e{_edge_to[vertex]}; e != nullptr; e = _edge_to[e.from()]) {
        path.push(e);
    }
    return path;
}

void Dijkstra_sp::_relax(Directed_edge& edge)
{
    auto v = edge.from();
    auto w = edge.to();
    if (_distance_to[w] > _distance_to[v] + edge.weight()) {
        _distance_to[w] = _distance_to[v] + edge.weight();
        _edge_to[w] = edge;
        if (_pq.contains(w)) { _pq.decreaseKey(w, _distance_to[w]); }
        else { _pq.insert(w, _distance_to[w]); }
    }
}

bool Dijkstra_sp::_check(Edge_weighted_digraph& digraph, int source)
{
    for (auto e : digraph.edges()) {
        if (e.weight() < 0) {
            std::cerr << "negative edge weight detected";
            return false;
        }
    }

    if (_distance_to[source] != 0.0 || _edge_to[source] != nullptr) {
        std::cerr << "_distance_to[s] and _edge_to[s] inconsistent";
        return false;
    }
    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        if (v == source) { continue; }
        if (_edge_to[v] == nullptr && _distance_to[v] != std::numeric_limits<double>::infinity()) {
            std::cerr << "_distance_to[] and _edge_to[] inconsistent";
            return false;
        }
    }

    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        for (auto e : digraph.adjacent(v)) {
            int w = e.to();
            if (_distance_to[v] + e.weight() < _distance_to[w]) {
                std::cerr << "edge " << e << " not relaxed";
                return false;
            }
        }
    }

    for (auto w = 0; w < digraph.num_vertices(); ++w) {
        if (_edge_to[w] == nullptr) { continue; }
        Directed_edge e{_edge_to[w]};
        auto v = e.from();
        if (w != e.to()) { return false; }
        if (_distance_to[v] + e.weight() != _distance_to[w]) {
            std::cerr << "edge " << e << " on shortest path not tight";
            return false;
        }
    }
    return true;
}
