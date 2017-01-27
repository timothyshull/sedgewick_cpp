#include "Depth_first_search.h"

Depth_first_search::Depth_first_search(Graph& graph, int source)
        : _marked(static_cast<std::deque<bool>::size_type>(graph.num_vertices())),
          _count{0}
{
    _dfs(graph, source);
}

void Depth_first_search::_dfs(Graph& G, int v)
{
    ++_count;
    _marked[v] = true;
    for (int w : G.adjacent(v)) {
        if (!_marked[w]) {
            _dfs(G, w);
        }
    }
}
