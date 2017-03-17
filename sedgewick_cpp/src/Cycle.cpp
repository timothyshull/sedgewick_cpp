#include "Cycle.h"

Cycle::Cycle(Graph& graph)
        : _marked(static_cast<std::deque<bool>::size_type>(graph.num_vertices())),
          _edge_to(static_cast<std::vector<int>::size_type>(graph.num_vertices()))
{
    if (_has_self_loop(graph)) { throw utility::Illegal_argument_exception{"The graph passed to the Cycle object has a self loop"}; }
    if (_has_parallel_edges(graph)) { throw utility::Illegal_argument_exception{"The graph passed to the Cycle object has parallel edges"}; }
    for (int v{0}; v < graph.num_vertices(); ++v) {
        if (!_marked[v]) {
            _dfs(graph, -1, v);
        }
    }
}

bool Cycle::_has_self_loop(Graph& graph)
{
    for (int v{0}; v < graph.num_vertices(); ++v) {
        for (auto w : graph.adjacent(v)) {
            if (v == w) {
                _cycle = Stack<int>{};
                _cycle.push(v);
                _cycle.push(v);
                return true;
            }
        }
    }
    return false;
}

bool Cycle::_has_parallel_edges(Graph& graph)
{
    _marked = std::deque<bool>(graph.num_vertices());

    for (int v{0}; v < graph.num_vertices(); ++v) {

        for (auto w : graph.adjacent(v)) {
            if (_marked[w]) {
                _cycle = Stack<int>{};
                _cycle.push(v);
                _cycle.push(w);
                _cycle.push(v);
                return true;
            }
            _marked[w] = true;
        }

        for (int w : graph.adjacent(v)) {
            _marked[w] = false;
        }
    }
    return false;
}

void Cycle::_dfs(Graph& graph, int u, int v)
{
    _marked[v] = true;
    for (auto w : graph.adjacent(v)) {

        if (!_cycle.is_empty()) { return; }

        if (!_marked[w]) {
            _edge_to[w] = v;
            _dfs(graph, v, w);
        } else if (w != u) {
            _cycle = Stack<int>{};
            for (int x{v}; x != w; x = _edge_to[x]) {
                _cycle.push(x);
            }
            _cycle.push(w);
            _cycle.push(v);
        }
    }
}
