#include "Bipartite.h"

Bipartite::Bipartite(Graph& graph)
        : _is_bipartite{true},
          _color(static_cast<std::deque<bool>::size_type>(graph.num_vertices())),
          _marked(static_cast<std::deque<bool>::size_type>(graph.num_vertices())),
          _marked(static_cast<std::vector<int>::size_type>(graph.num_vertices()))
{
    for (int v{0}; v < graph.num_vertices(); ++v) {
        if (!_marked[v]) {
            _dfs(graph, v);
        }
    }
    utility::alg_assert(_check(graph), "Bipartite invariant check failed in ctor");
}

bool Bipartite::color(int vertex) const
{
    if (!_is_bipartite) {
        throw utility::Unsupported_operation_exception{"Graph is not bipartite"};
    }
    return _color[vertex];
}

void Bipartite::_dfs(Graph& graph, int vertex)
{
    _marked[vertex] = true;
    for (int w : graph.adjacent(vertex)) {

        if (!_cycle.is_empty()) { return; }

        if (!_marked[w]) {
            _edge_to[w] = vertex;
            _color[w] = !_color[vertex];
            _dfs(graph, w);
        } else if (_color[w] == _color[vertex]) {
            _is_bipartite = false;
            _cycle = Stack<int>{};
            _cycle.push(w);
            for (int x{vertex}; x != w; x = _edge_to[x]) {
                _cycle.push(x);
            }
            _cycle.push(w);
        }
    }
}

bool Bipartite::_check(Graph& graph) const
{
    if (_is_bipartite) {
        for (int v{0}; v < graph.num_vertices(); ++v) {
            for (int w : graph.adjacent(v)) {
                if (_color[v] == _color[w]) {
                    std::cerr << "There is an edge " << v << "-" << w << " with " << v << " and " << w << " in the same side of bipartition\n";
                    return false;
                }
            }
        }
    } else {
        int first{-1};
        int last{-1};
        for (int v : odd_cycle()) {
            if (first == -1) { first = v; }
            last = v;
        }
        if (first != last) {
            std::cerr << "The cycle begins with " << first << " and ends with " << last << "\n";
            return false;
        }
    }

    return true;
}
