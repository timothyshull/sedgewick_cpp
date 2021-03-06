#include <gsl/gsl_util>

#include "Bellman_ford_sp.h"
#include "Edge_weighted_directed_cycle.h"
#include "Std_out.h"

Bellman_ford_sp::Bellman_ford_sp(Edge_weighted_digraph digraph, int source)
        : _distance_to(digraph.num_vertices()), std::numeric_limits<double>::infinity(),
          _edge_to(digraph.num_vertices()),
          _on_queue(digraph.num_vertices()),
          _queue{}
{
    _distance_to[source] = 0.0;
    _queue.enqueue(source);
    _on_queue[source] = true;
    while (!_queue.is_empty() && !has_negative_cycle()) {
        auto v = _queue.dequeue();
        _on_queue[v] = false;
        _relax(digraph, v);
    }

    utility::alg_assert(_check(digraph, source), "Bellman_ford_sp invariant check failed after construction");
}

bool Bellman_ford_sp::has_negative_cycle()
{
    return !_cycle.is_empty();
}

Stack<Directed_edge> Bellman_ford_sp::negative_cycle()
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

Stack<Directed_edge> Bellman_ford_sp::path_to(int vertex)
{
    if (has_negative_cycle()) {
        throw utility::Unsupported_operation_exception{"Negative _cost _cycle exists"};
    }
    if (!has_path_to(vertex)) { return {}; }
    Stack<Directed_edge> path;
    for (Directed_edge e{_edge_to[vertex]}; e != Directed_edge{}; e = _edge_to[e.from()]) {
        path.push(e);
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
    auto num_vertices = gsl::narrow<int, std::vector<Directed_edge>::size_type>(_edge_to.size());
    Edge_weighted_digraph spt{num_vertices};
    for (auto v = 0; v < num_vertices; ++v) {
        if (_edge_to[v] != Directed_edge{}) {
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

        if (_distance_to[source] != 0.0 || _edge_to[source] != Directed_edge{}) {
            std::cerr << "distanceTo[s] and _edge_to[s] inconsistent";
            return false;
        }

        for (auto v = 0; v < digraph.num_vertices(); ++v) {
            if (v == source) { continue; }
            if (_edge_to[v] == Directed_edge{} && _distance_to[v] != std::numeric_limits<double>::infinity()) {
                std::cerr << "_distance_to[] and _edge_to[] inconsistent";
                return false;
            }
        }

        for (auto v = 0; v < digraph.num_vertices(); ++v) {
            for (Directed_edge e : digraph.adjacent(v)) {
                int w = e.to();
                if (_distance_to[v] + e.weight() < _distance_to[w]) {
                    std::cerr << "edge " << e << " not relaxed";
                    return false;
                }
            }
        }

        for (auto w = 0; w < digraph.num_vertices(); ++w) {
            if (_edge_to[w] == Directed_edge{}) { continue; }
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
