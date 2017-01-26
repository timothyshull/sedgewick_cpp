#include "Bellman_ford_sp.h"
#include "Edge_weighted_directed_cycle.h"
#include "Std_out.h"

Bellman_ford_sp::Bellman_ford_sp(Edge_weighted_digraph digraph, int source)
        : _distance_to(static_cast<std::vector<double>::size_type>(digraph.num_vertices()), std::numeric_limits<double>::infinity()),
          _edge_to(static_cast<std::vector<Directed_edge>::size_type>(digraph.num_vertices())),
          _on_queue(static_cast<std::deque<bool>::size_type>(digraph.num_vertices())),
          _queue{}
{
    _distance_to[source] = 0.0;
    _queue.enqueue(source);
    _on_queue[source] = true;
    int v;
    while (!_queue.is_empty() && !has_negative_cycle()) {
        v = _queue.dequeue();
        _on_queue[v] = false;
        _relax(digraph, v);
    }

    utility::alg_assert(_check(digraph, source), "Bellman_ford_sp invariant check failed after construction");
}

bool Bellman_ford_sp::has_negative_cycle()
{
    return !_cycle.empty();
}

std::vector<Directed_edge> Bellman_ford_sp::negative_cycle()
{
    return _cycle;
}

double Bellman_ford_sp::distance_to(int vertex)
{
    if (has_negative_cycle()) {
        throw utility::Unsupported_operation_exception{"Negative cost cycle exists"};
    }
    return _distance_to[vertex];
}

bool Bellman_ford_sp::has_path_to(int vertex)
{
    return _distance_to[vertex] < std::numeric_limits<double>::infinity();
}

std::vector<Directed_edge> Bellman_ford_sp::path_to(int vertex)
{
    if (has_negative_cycle()) {
        throw utility::Unsupported_operation_exception("Negative _cost _cycle exists");
    }
    if (!has_path_to(vertex)) { return {}; }
    std::vector<Directed_edge> path;
    for (Directed_edge e{_edge_to[vertex]}; e != null; e = _edge_to[e.from()]) {
        path.emplace_back(e);
    }
    return path;
}

void Bellman_ford_sp::_relax(Edge_weighted_digraph digraph, int vertex)
{
    for (Directed_edge e : digraph.adjacent(vertex)) {
        int w = e.to();
        if (_distance_to[w] > _distance_to[vertex] + e.weight()) {
            _distance_to[w] = _distance_to[vertex] + e.weight();
            _edge_to[w] = e;
            if (!_on_queue[w]) {
                _queue.enqueue(w);
                _on_queue[w] = true;
            }
        }
        if (_cost++ % digraph.num_vertices() == 0) {
            _find_negative_cycle();
            if (has_negative_cycle()) { return; }
        }
    }
}

void Bellman_ford_sp::_find_negative_cycle()
{
    int num_vertices = static_cast<int>(_edge_to.size());
    Edge_weighted_digraph spt{num_vertices};
    for (int v{0}; v < num_vertices; ++v) {
        if (_edge_to[v] != null) {
            spt.add_edge(_edge_to[v]);
        }
    }

    Edge_weighted_directed_cycle finder{spt};
    _cycle = finder.cycle();
}

bool Bellman_ford_sp::_check(Edge_weighted_digraph digraph, int source)
{
    if (has_negative_cycle()) {
        double weight{0.0};
        for (Directed_edge e : negative_cycle()) {
            weight += e.weight();
        }
        if (weight >= 0.0) {
            std::cerr << "error: weight of negative _cycle = " + std::to_string(weight);
            return false;
        }
    } else {

        if (_distance_to[source] != 0.0 || _edge_to[source] != null) {
            std::cerr << "distanceTo[s] and _edge_to[s] inconsistent";
            return false;
        }

        for (int v{0}; v < digraph.num_vertices(); ++v) {
            if (v == source) { continue; }
            if (_edge_to[v] == null && _distance_to[v] != std::numeric_limits<double>::infinity()) {
                std::cerr << "_distance_to[] and _edge_to[] inconsistent";
                return false;
            }
        }

        for (int v{0}; v < digraph.num_vertices(); ++v) {
            for (Directed_edge e : digraph.adjacent(v)) {
                int w = e.to();
                if (_distance_to[v] + e.weight() < _distance_to[w]) {
                    std::cerr << "edge " + e + " not relaxed");
                    return false;
                }
            }
        }

        for (int w{0}; w < digraph.num_vertices(); ++w) {
            if (_edge_to[w] == null) { continue; }
            Directed_edge e = _edge_to[w];
            int v = e.from();
            if (w != e.to()) { return false; }
            if (_distance_to[v] + e.weight() != _distance_to[w]) {
                std::cerr << "edge " + e.to_string() + " on shortest path not tight";
                return false;
            }
        }
    }

    Std_out::print_line("Satisfies optimality conditions");
    Std_out::print_line();
    return true;
}
