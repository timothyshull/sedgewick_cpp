#include <iostream>
#include "Edge_weighted_directed_cycle.h"

Edge_weighted_directed_cycle::Edge_weighted_directed_cycle(Edge_weighted_digraph& digraph)
        : _marked(static_cast<std::deque<bool>::size_type>(digraph.num_vertices())),
          _on_stack(static_cast<std::deque<bool>::size_type>(digraph.num_vertices())),
          _edge_to(static_cast<std::vector<int>::size_type>(digraph.num_vertices())),
          _cycle{}
{
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        if (!_marked[v]) {
            _dfs(digraph, v);
        }
    }

    utility::alg_assert(_check(digraph), "Edge_weighted_directed_cycle invariant check failed in constructor");
}

void Edge_weighted_directed_cycle::_dfs(Edge_weighted_digraph& digraph, int vertex)
{
    _on_stack[vertex] = true;
    _marked[vertex] = true;
    int w;
    for (auto e : digraph.adjacent(vertex)) {
        w = e.to();

        if (!_cycle.is_empty()) {
            return;
        } else if (!_marked[w]) {
            _edge_to[w] = e;
            _dfs(digraph, w);
        } else if (_on_stack[w]) {
            _cycle = Stack<Directed_edge>{};

            Directed_edge f = e;
            while (f.from() != w) {
                _cycle.push(f);
                f = _edge_to[f.from()];
            }
            _cycle.push(f);
            return;
        }
    }

    _on_stack[vertex] = false;
}

bool Edge_weighted_directed_cycle::_check(Edge_weighted_digraph& digraph) const
{
    if (has_cycle()) {
//        auto tmp = cycle();
//        for (auto it = _cycle.begin(); it != _cycle.end(); ++it) {
//            std::cerr << *it << "\n";
//        }
        Directed_edge first;
        Directed_edge last;
        for (auto e : cycle()) {
            if (first == Directed_edge{}) { first = e; }
            if (last != Directed_edge{}) {
                if (last.to() != e.from()) {
                    std::cerr << "The cycle edges " << last << " and " << e << " are not incident 1\n";
                    return false;
                }
            }
            last = e;
        }

        if (last.to() != first.from()) {
            std::cerr << "The cycle edges " << last << " and " << first << " are not incident 2\n";
            return false;
        }
    }

    return true;
}
