#include "Floyd_warshall.h"
#include "Edge_weighted_digraph.h"
#include "Edge_weighted_directed_cycle.h"

Floyd_warshall::Floyd_warshall(Adj_matrix_edge_weighted_digraph& digraph)
        : _distances(static_cast<std::vector<std::vector<double>>::size_type>(digraph.num_vertices())),
          _edge_to(static_cast<std::vector<std::vector<Directed_edge>>::size_type>(digraph.num_vertices()))
{
    int num_vertices = digraph.num_vertices();

    for (auto v = 0; v < num_vertices; ++v) {
        for (auto w = 0; w < num_vertices; ++w) {
            _distances[v][w] = std::numeric_limits<double>::infinity();
        }
    }

    for (auto v = 0; v < num_vertices; ++v) {
        for (auto e : digraph.adjacent(v)) {
            _distances[e.from()][e.to()] = e.weight();
            _edge_to[e.from()][e.to()] = e;
        }
        if (_distances[v][v] >= 0.0) {
            _distances[v][v] = 0.0;
            _edge_to[v][v] = nullptr;
        }
    }

    for (auto i = 0; i < num_vertices; ++i) {
        for (auto v = 0; v < num_vertices; ++v) {
            if (_edge_to[v][i] == nullptr) { continue; }
            for (auto w = 0; w < num_vertices; ++w) {
                if (_distances[v][w] > _distances[v][i] + _distances[i][w]) {
                    _distances[v][w] = _distances[v][i] + _distances[i][w];
                    _edge_to[v][w] = _edge_to[i][w];
                }
            }
            if (_distances[v][v] < 0.0) {
                _has_negative_cycle = true;
                return;
            }
        }
    }
    utility::alg_assert(_check(digraph), "Floyd_warshall invariant check failed after construction");
}

Stack<Directed_edge> Floyd_warshall::negative_cycle()
{
    int num_vertices;
    for (auto v = 0; v < _distances.size(); ++v) {
        if (_distances[v][v] < 0.0) {
            num_vertices = static_cast<int>(_edge_to.size());
            Edge_weighted_digraph spt{num_vertices};
            for (auto w = 0; w < num_vertices; ++w) {
                if (_edge_to[v][w] != Directed_edge{}) {
                    spt.add_edge(_edge_to[v][w]);
                }
            }
            Edge_weighted_directed_cycle finder{spt};
            utility::alg_assert(finder.has_cycle(), "Floyd_warshall has_cycle() check failed in negative_cycle()");
            return finder.cycle();
        }
    }
    return {};
}

double Floyd_warshall::distance(int s, int t)
{
    if (has_negative_cycle()) {
        throw utility::Unsupported_operation_exception{"Negative cost cycle exists"};
    }
    return _distances[s][t];
}

std::vector<Directed_edge> Floyd_warshall::path(int source, int dest)
{
    if (has_negative_cycle()) {
        throw utility::Unsupported_operation_exception{"Negative cost cycle exists"};
    }
    if (!has_path(source, dest)) { return {}; }
    std::vector<Directed_edge> path;
    for (Directed_edge e{_edge_to[source][dest]}; e != Directed_edge{}; e = _edge_to[source][e.from()]) {
        path.push_back(e);
    }
    return path;
}

bool Floyd_warshall::_check(Adj_matrix_edge_weighted_digraph& digraph)
{
    if (!has_negative_cycle()) {
        for (auto v = 0; v < digraph.num_vertices(); ++v) {
            for (Directed_edge e : digraph.adjacent(v)) {
                int w = e.to();
                for (auto i = 0; i < digraph.num_vertices(); ++i) {
                    if (_distances[i][w] > _distances[i][v] + e.weight()) {
                        std::cerr << "edge " << e << " is eligible";
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
