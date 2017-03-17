// Program 18.1 - Depth-first search of a connected component
#ifndef CONNECTED_COMPONENT_DFS_H
#define CONNECTED_COMPONENT_DFS_H

#include <vector>

template<typename Graph>
class Connected_component_dfs {
public:
    Connected_component_dfs(const Graph& graph, int v = 0)
            : _graph{graph},
              _count{0},
              _order(graph.num_vertices(), -1) { _search_c(v); }

    inline int count() const { return _count; }

    inline int operator[](int v) const { return _order[v]; }
private:
    int _count;
    const Graph& _graph;
    std::vector<int> _order;

    void _search_c(int v)
    {
        _order[v] = _count++;
        // typename Graph::adjIterator A(_graph, v);
        for (auto t : _graph.adjacent(v)) {
            if (_order[t] == -1) { _search_c(t); }
        }
    }
};

#endif // CONNECTED_COMPONENT_DFS_H
