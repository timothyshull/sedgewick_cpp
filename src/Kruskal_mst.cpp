#include "Kruskal_mst.h"
#include "Min_pq.h"
#include "Union_find.h"

Kruskal_mst::Kruskal_mst(Edge_weighted_graph& graph)
{
    Min_pq<Edge> pq;
    for (auto e : graph.edges()) {
        pq.insert(e);
    }

    Union_find uf{graph.num_vertices()};
    int v;
    int w;
    while (!pq.is_empty() && _mst.size() < graph.num_vertices() - 1) {
        Edge e = pq.delete_min();
        v = e.either();
        w = e.other(v);
        if (!uf.connected(v, w)) {
            uf.create_union(v, w);
            _mst.enqueue(e);
            _weight += e.weight();
        }
    }

    utility::alg_assert(_check(graph), "Kruskal_mst invariant check failed after construction");
}

bool Kruskal_mst::_check(Edge_weighted_graph& graph)
{
    double total{0.0};
    for (auto e : edges()) {
        total += e.weight();
    }
    if (std::abs(total - weight()) > _floating_point_epsilon) {
        std::cerr << "Weight of edges does not equal weight(): " << total << " vs. " << weight() << "\n";
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
