#include "Directed_dfs.h"

Directed_dfs::Directed_dfs(Digraph& digraph, int source)
        : _marked(static_cast<std::deque<bool>::size_type>(digraph.num_vertices()))
{
    _dfs(digraph, source);
}

Directed_dfs::Directed_dfs(Digraph& digraph, std::vector<int>& sources)
: _marked(static_cast<std::deque<bool>::size_type>(digraph.num_vertices()))
{
    for (auto v : sources) {
        if (!_marked[v]) {
            _dfs(digraph, v);
        }
    }
}

void Directed_dfs::_dfs(Digraph& digraph, int vertex)
{
    ++_count;
    _marked[vertex] = true;
    for (int w : digraph.adjacent(vertex)) {
        if (!_marked[w]) { _dfs(digraph, w); }
    }
}
