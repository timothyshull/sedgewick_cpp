#include "Lazy_prim_mst.h"
#include "Union_find.h"

Lazy_prim_mst::Lazy_prim_mst(Edge_weighted_graph& graph)
        : _mst{},
          _pq{},
          _marked(static_cast<std::deque<bool>::size_type>(graph.num_vertices()))
{
    for (int v{0}; v < graph.num_vertices(); ++v) {
        if (!_marked[v]) { prim(graph, v); }
    }

    utility::alg_assert(_check(graph), "Lazy_prim_mst invariant check failed after construction");
}

void Lazy_prim_mst::prim(Edge_weighted_graph& graph, int source)
{
    scan(graph, source);
    int v;
    int w;
    while (!_pq.is_empty()) {
        Edge e = _pq.delete_min();
        v = e.either();
        w = e.other(v);
        utility::alg_assert(_marked[v] || _marked[w], "Lazy_prim_mst prim() check that v or w is marked failed");
        if (_marked[v] && _marked[w]) { continue; }
        _mst.enqueue(e);
        _weight += e.weight();
        if (!_marked[v]) { scan(graph, v); }
        if (!_marked[w]) { scan(graph, w); }
    }
}

void Lazy_prim_mst::scan(Edge_weighted_graph& graph, int vertex)
{
    utility::alg_assert(!_marked[vertex], "Lazy_prim_mst scan check that the vertex is not marked failed");
    _marked[vertex] = true;
    for (auto e : graph.adjacent(vertex)) {
        if (!_marked[e.other(vertex)]) { _pq.insert(e); }
    }
}

bool Lazy_prim_mst::_check(Edge_weighted_graph& graph)
{
    double total_weight{0.0};
    for (auto e : edges()) {
        total_weight += e.weight();
    }
    if (std::abs(total_weight - weight()) > _floating_point_epsilon) {
        std::cerr << "Weight of edges does not equal weight(): " << total_weight << " vs. " << weight() << "\n";
        return false;
    }

    Union_find uf{graph.num_vertices()};
    int v;
    int w;
    for (auto e : edges()) {
        v = e.either();
        w = e.other(v);
        if (uf.connected(v, w)) {
            std::cerr << "Not a forest";
            return false;
        }
        uf.create_union(v, w);
    }

    for (auto e : graph.edges()) {
        v = e.either();
        w = e.other(v);
        if (!uf.connected(v, w)) {
            std::cerr << "Not a spanning forest";
            return false;
        }
    }

    int x;
    int y;
    for (auto e : edges()) {
        uf = Union_find{graph.num_vertices()};
        for (auto f : _mst) {
            x = f.either();
            y = f.other(x);
            if (f != e) { uf.create_union(x, y); }
        }

        for (auto f : graph.edges()) {
            x = f.either();
            y = f.other(x);
            if (!uf.connected(x, y)) {
                if (f.weight() < e.weight()) {
                    std::cerr << "Edge " << f << " violates cut optimality conditions";
                    return false;
                }
            }
        }

    }

    return true;
}
