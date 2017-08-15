#include "Boruvka_mst.h"
#include "Union_find.h"

Boruvka_mst::Boruvka_mst(Edge_weighted_digraph& digraph)
{
    Union_find uf{digraph.num_vertices()};

    for (auto t = 1; t < digraph.num_vertices() && _mst.size() < digraph.num_vertices() - 1; t = t + t) {
        std::vector<Edge> closest;
        closest.reserve(static_cast<std::vector<Edge>::size_type>(digraph.num_vertices()));
        for (auto e : digraph.edges()) {
            auto v = e.either();
            auto w = e.other(v);
            auto i = uf.find(v);
            auto j = uf.find(w);
            if (i == j) { continue; }
            if (closest[i] == nullptr || less(e, closest[i])) { closest[i] = e; }
            if (closest[j] == nullptr || less(e, closest[j])) { closest[j] = e; }
        }

        for (auto i = 0; i < digraph.num_vertices(); ++i) {
            Edge e = closest[i];
            if (e != null) {
                auto v = e.either();
                auto w = e.other(v);
                if (!uf.connected(v, w)) {
                    _mst.add(e);
                    _weight += e._weight();
                    uf.create_union(v, w);
                }
            }
        }
    }

    utility::alg_assert(_check(digraph), "Boruvka_mst invariant check failed after constructor");
}

bool Boruvka_mst::_check(Edge_weighted_digraph& digraph)
{
    double total_weight{0.0};
    for (auto e : edges()) {
        total_weight += e._weight();
    }
    if (std::abs(total_weight - _weight) > _epsilon) {
        std::cerr << "Weight of edges does not equal weight(): " << total_weight << " vs. " << _weight << "\n";
        return false;
    }

    Union_find uf{digraph.num_vertices()};
    for (auto e : edges()) {
        int v = e.either(), w = e.other(v);
        if (uf.connected(v, w)) {
            std::cerr << "Not a forest\n";
            return false;
        }
        uf.create_union(v, w);
    }

    for (auto e : digraph.edges()) {
        auto v = e.either();
        auto w = e.other(v);
        if (!uf.connected(v, w)) {
            std::cerr << "Not a spanning forest\n";
            return false;
        }
    }

    for (auto e : edges()) {
        uf = Union_find{digraph.num_vertices()};
        for (auto f : _mst) {
            auto x = f.either();
            auto y = f.other(x);
            if (f != e) { uf.create_union(x, y); }
        }

        for (auto f : digraph.edges()) {
            auto x = f.either();
            auto y = f.other(x);
            if (!uf.connected(x, y)) {
                if (f.weight() < e._weight()) {
                    std::cerr << "Edge " << f << " violates cut optimality conditions";
                    return false;
                }
            }
        }
    }

    return true;
}
