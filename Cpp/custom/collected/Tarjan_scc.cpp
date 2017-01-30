#include "Tarjan_scc.h"
#include "Transitive_closure.h"

Tarjan_scc::Tarjan_scc(Digraph& digraph)
        : _marked(static_cast<std::deque<bool>::size_type>(digraph.num_vertices())),
          _stack{},
          _id(static_cast<std::vector<int>::size_type>(digraph.num_vertices())),
          _low(static_cast<std::vector<int>::size_type>(digraph.num_vertices()))
{
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        if (!_marked[v]) { _dfs(digraph, v); }
    }

    utility::alg_assert(_check(digraph), "Tarjan_scc invariant check failed after construction");
}

void Tarjan_scc::_dfs(Digraph& digraph, int vertex)
{
    _marked[vertex] = true;
    _low[vertex] = ++_pre;
    int min = _low[vertex];
    _stack.push(vertex);
    for (int w : digraph.adjacent(vertex)) {
        if (!_marked[w]) { _dfs(digraph, w); }
        if (_low[w] < min) { min = _low[w]; }
    }
    if (min < _low[vertex]) {
        _low[vertex] = min;
        return;
    }
    int w;
    do {
        w = _stack.pop();
        _id[w] = _count;
        _low[w] = digraph.num_vertices();
    } while (w != vertex);
    ++_count;
}

bool Tarjan_scc::_check(Digraph& digraph)
{
    Transitive_closure tc{digraph};
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        for (int w{0}; w < digraph.num_vertices(); ++w) {
            if (strongly_connected(v, w) != (tc.reachable(v, w) && tc.reachable(w, v))) {
                return false;
            }
        }
    }
    return true;
}
