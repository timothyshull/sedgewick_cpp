#include "Depth_first_directed_paths.h"

Depth_first_directed_paths::Depth_first_directed_paths(Digraph& digraph, int source)
        : _marked(static_cast<std::deque<bool>::size_type>(digraph.num_vertices())),
          _edge_to(static_cast<std::vector<int>::size_type>(digraph.num_vertices())),
          _source{source}
{
    _dfs(digraph, source);
}

Stack<int> Depth_first_directed_paths::path_to(int vertex) const
{
    if (!has_path_to(vertex)) { return {}; }
    Stack<int> path;
    for (int x{vertex}; x != _source; x = _edge_to[x]) {
        path.push(x);
    }
    int tmp{_source};
    path.push(tmp);
    return path;
}

void Depth_first_directed_paths::_dfs(Digraph& digraph, int vertex)
{
    _marked[vertex] = true;
    for (int w : digraph.adjacent(vertex)) {
        if (!_marked[w]) {
            _edge_to[w] = vertex;
            _dfs(digraph, w);
        }
    }
}
