#include <iostream>
#include "Edge_weighted_directed_cycle.h"

Edge_weighted_directed_cycle::Edge_weighted_directed_cycle(Edge_weighted_digraph& g)
        : _marked(static_cast<std::deque<bool>::size_type>(g.num_vertices())),
          _on_stack(static_cast<std::deque<bool>::size_type>(g.num_vertices())),
          _edge_to(static_cast<std::vector<int>::size_type>(g.num_vertices()))
{
    for (int v{0}; v < g.num_vertices(); ++v) {
        if (!_marked[v]) {
            _dfs(g, v);
        }
    }

    utility::alg_assert(_check(g), "Edge_weighted_directed_cycle invariant _check failed _in constructor");
}

void Edge_weighted_directed_cycle::_dfs(Edge_weighted_digraph& g, int v)
{
    _on_stack[v] = true;
    _marked[v] = true;
    for (Directed_edge e : g.adjacent(v)) {
        int w = e.to();

        if (!_cycle.is_empty()) {
            return;
        } else if (!_marked[w]) {
            _edge_to[w] = e;
            _dfs(g, w);
        } else if (_on_stack[w]) {
            Directed_edge f = e;
            while (f.from() != w) {
                _cycle.push(f);
                f = _edge_to[f.from()];
            }
            _cycle.push(f);
            return;
        }
    }

    _on_stack[v] = false;
}

bool Edge_weighted_directed_cycle::_check(Edge_weighted_digraph& g) const
{
    if (has_cycle()) {
        Directed_edge* first = nullptr;
        Directed_edge* last = nullptr;
        for (Directed_edge e : cycle()) {
            if (first == nullptr) { first = &e; }
            if (last != nullptr) {
                if (last->to() != e.from()) {
                    std::stringstream ss;
                    ss << "The _cycle edges " << *last << " and " << e << " are not incident\n";
                    std::cerr << ss.str();
                    return false;
                }
            }
            last = &e;
        }

        if ((last && first) && (last->to() != first->from())) {
            std::stringstream ss;
            ss << "The _cycle edges " << *last << " and " << *first << " are not incident\n";
            std::cerr << ss.str();
            return false;
        }
    }

    return true;
}
