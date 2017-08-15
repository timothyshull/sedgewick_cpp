#include "Depth_first_paths.h"

Depth_first_paths::Depth_first_paths(Digraph& digraph, int source)
        : _marked(static_cast<std::deque<bool>::size_type>(digraph.num_vertices())),
          _edge_to(static_cast<std::vector<int>::size_type>(digraph.num_vertices())),
          _source{source}
{
    _dfs(digraph, source);
}

Stack<int> Depth_first_paths::path_to(int v)
{
    if (!has_path_to(v)) { return {}; }
    Stack<int> path;
    for (auto x = v; x != _source; x = _edge_to[x]) {
        path.push(x);
    }
    auto tmp = _source;
    path.push(tmp);
    return path;
}

void Depth_first_paths::_dfs(Digraph& G, int v)
{
    _marked[v] = true;
    for (int w : G.adjacent(v)) {
        if (!_marked[w]) {
            _edge_to[w] = v;
            _dfs(G, w);
        }
    }
}
