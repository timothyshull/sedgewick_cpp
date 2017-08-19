#include "Dijkstra_undirected_sp.h"
#include "Edge.h"

Dijkstra_undirected_sp::Dijkstra_undirected_sp(Edge_weighted_digraph& digraph, int source)
        : _distance_to(static_cast<std::vector<double>::size_type>(digraph.num_vertices())),
          _edge_to(static_cast<std::vector<Edge>::size_type>(digraph.num_vertices())),
          _pq{digraph.num_vertices()}
{
    for (auto e : digraph.edges()) {
        if (e.weight() < 0) {
            std::string s{"edge " + e.to_string() + " has negative weight"};
            throw utility::Illegal_argument_exception{s};
        }
    }

    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        _distance_to[v] = std::numeric_limits<double>::infinity();
    }
    _distance_to[source] = 0.0;

    _pq.insert(source, _distance_to[source]);
    while (!_pq.is_empty()) {
        int v = _pq.delMin();
        for (auto e : digraph.adjacent(v)) {
            _relax(e, v);
        }
    }

    utility::alg_assert(_check(digraph, source), "Dijkstra_undirected_sp invariant check failed after construction");
}

Stack<Directed_edge> Dijkstra_undirected_sp::path_to(int v)
{
    if (!has_path_to(v)) { return nullptr; }
    Stack<Edge> path;
    auto x = v;
    for (Edge e{_edge_to[v]}; e != nullptr; e = _edge_to[x]) {
        path.push(e);
        x = e.other(x);
    }
    return path;
}

void Dijkstra_undirected_sp::_relax(Directed_edge& e, int v)
{
    auto w = e.other(v);
    if (_distance_to[w] > _distance_to[v] + e.weight()) {
        _distance_to[w] = _distance_to[v] + e.weight();
        _edge_to[w] = e;
        if (_pq.contains(w)) { _pq.decreaseKey(w, _distance_to[w]); }
        else { _pq.insert(w, _distance_to[w]); }
    }
}

bool Dijkstra_undirected_sp::_check(Edge_weighted_digraph& digraph, int source)
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
            int w = e.other(v);
            if (_distance_to[v] + e.weight() < _distance_to[w]) {
                std::cerr << "edge " << e << " not relaxed";
                return false;
            }
        }
    }

    for (auto w = 0; w < digraph.num_vertices(); ++w) {
        if (_edge_to[w] == nullptr) { continue; }
        Edge e = _edge_to[w];
        if (w != e.either() && w != e.other(e.either())) { return false; }
        int v = e.other(w);
        if (_distance_to[v] + e.weight() != _distance_to[w]) {
            std::cerr << "edge " << e.to_string() << " on shortest path not tight";
            return false;
        }
    }
    return true;
}
