#include "Connected_component.h"

Connected_component::Connected_component(Graph& graph)
        : _marked(static_cast<std::deque<bool>::size_type>(graph.num_vertices())),
          _id(static_cast<std::vector<int>::size_type>(graph.num_vertices())),
          _size(static_cast<std::vector<int>::size_type>(graph.num_vertices()))
{
    for (int v{0}; v < graph.num_vertices(); ++v) {
        if (!_marked[v]) {
            _dfs(graph, v);
            ++_count;
        }
    }
}

void Connected_component::_dfs(Graph& G, int v)
{
    _marked[v] = true;
    _id[v] = _count;
    _size[_count]++;
    for (int w : G.adjacent(v)) {
        if (!_marked[w]) {
            _dfs(G, w);
        }
    }
}
