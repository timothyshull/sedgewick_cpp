#include "Prim_mst.h"
#include "Union_find.h"

Prim_mst::Prim_mst(Edge_weighted_graph& graph)
: _edge_to(static_cast<std::vector<Edge>::size_type>(graph.num_vertices())),
  _distance_to(static_cast<std::vector<double>::size_type>(graph.num_vertices())),
  _marked(static_cast<std::deque<bool>::size_type>(graph.num_vertices())),
  _pq{graph.num_vertices()}
{
    for (int v{0}; v < graph.num_vertices(); ++v) {
        _distance_to[v] = std::numeric_limits<double>::infinity();
    }

    for (int v{0}; v < graph.num_vertices(); ++v) {
        if (!_marked[v]) { _prim(graph, v); }
    }

    utility::alg_assert(_check(graph), "Prim_mst check failed after construction");
}

Queue<Edge> Prim_mst::edges()
{
    Queue <Edge> mst;
    for (int v{0}; v < _edge_to.size(); ++v) {
        Edge e = _edge_to[v];
        if (e != nullptr) {
            mst.enqueue(e);
        }
    }
    return mst;
}

double Prim_mst::weight()
{
    double weight{0.0};
    for (auto e : edges()) {
        weight += e.weight();
    }
    return weight;
}

void Prim_mst::_prim(Edge_weighted_graph& graph, int source)
{
    _distance_to[source] = 0.0;
    _pq.insert(source, _distance_to[source]);
    int v;
    while (!_pq.is_empty()) {
        v = _pq.delMin();
        _scan(graph, v);
    }
}

void Prim_mst::_scan(Edge_weighted_graph& graph, int vertex)
{
    _marked[vertex] = true;
    for (auto e : graph.adjacent(vertex)) {
        int w = e.other(vertex);
        if (_marked[w]) { continue; }
        if (e.weight() < _distance_to[w]) {
            _distance_to[w] = e.weight();
            _edge_to[w] = e;
            if (_pq.contains(w)) _pq.decreaseKey(w, _distance_to[w]);
            else _pq.insert(w, _distance_to[w]);
        }
    }
}

bool Prim_mst::_check(Edge_weighted_graph& graph)
{
    double total_weight{0.0};
    for (auto e : edges()) {
        total_weight += e.weight();
    }
    if (std::abs(total_weight - weight()) > floating_point_epsilon) {
        std::cerr << "Weight of edges does not equal weight(): "<< total_weight << " vs. " << weight() << "\n";
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
        for (auto f : edges()) {
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
