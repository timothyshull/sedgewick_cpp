#include "Directed_cycle.h"

Directed_cycle::Directed_cycle(Digraph& g)
        : _marked(static_cast<std::deque<int>::size_type>(g.num_vertices())),
          _on_stack(static_cast<std::deque<int>::size_type>(g.num_vertices())),
          _edge_to(static_cast<std::vector<int>::size_type>(g.num_vertices()))
{
    for (int v{0}; v < g.num_vertices(); ++v) {
        if (!_marked[v] && _cycle.is_empty()) {
            _dfs(g, v);
        }
    }
}

void Directed_cycle::_dfs(Digraph& g, int v)
{
    _on_stack[v] = true;
    _marked[v] = true;

    for (auto w : g.adjacent(v)) {
        if (!_cycle.is_empty()) {
            return;
        } else if (!_marked[w]) {
            _edge_to[w] = v;
            _dfs(g, w);
        } else if (_on_stack[w]) {
            _cycle = Stack<int>();
            for (int x{v}; x != w; x = _edge_to[x]) {
                _cycle.push(x);
            }
            _cycle.push(w);
            _cycle.push(v);
            utility::alg_assert(_check(), "Directed_cycle invariant _check failed after _dfs()");
        }
    }
}

bool Directed_cycle::_check() const
{
    if (has_cycle()) {
        int first = -1;
        int last = -1;
        for (int v : cycle()) {
            if (first == -1) {
                first = v;
            }
            last = v;
        }
        if (first != last) {
            std::stringstream ss;
            ss << "The _cycle begins with " << first << " and ends with " << last << "\n";
            return false;
        }
    }
    return true;
}

Stack<int> Directed_cycle::cycle() const
{
    return _cycle;
}
