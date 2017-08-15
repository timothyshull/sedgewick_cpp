#ifndef DERIVED_DFS_H
#define DERIVED_DFS_H

#include "Generalized_graph_search.h"

template<typename Graph_type>
class Derived_dfs : public Generalized_graph_search<Graph_type> {
public:
    Derived_dfs(const Graph_type& graph)
            : Generalized_graph_search<Graph_type>{graph},
              _search_tree(graph.num_vertices(), -1) { _search(); }

    inline int search_tree(int v) const { return _search_tree[v]; }

private:
    std::vector<int> _search_tree;

    void _search_c(Edge&& e)
    {
        auto w = e.destination();
        _order[w] = _count++;
        _search_tree[e.destination()] = e.source();
        // typename Graph_type::adjIterator A(G, w);
        for (auto t : _graph.adjacent(w)) {
            if (_order[t] == -1) { _search_c(Edge{w, t}); }
        }
    }
};

#endif // DERIVED_DFS_H
