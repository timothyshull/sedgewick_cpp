#ifndef DERIVED_BFS_IMPROVED_H
#define DERIVED_BFS_IMPROVED_H

#include <queue>

#include "Generalized_graph_search.h"

template<typename Graph_type>
class Derived_bfs_improved : public Generalized_graph_search<Graph_type> {
public:
    Derived_bfs_improved(Graph_type& graph)
            : Generalized_graph_search<Graph_type>{graph},
              _search_tree(graph.num_vertices(), -1) { _search(); }

    inline int search_tree(int v) const { return _search_tree[v]; }

private:
    std::vector<int> _search_tree;

    void _search_c(Edge&& e)
    {
        std::queue<Edge> queue;
        queue.push(e);
        _order[e.destination()] = _count++;
        Edge tmp;
        while (!queue.empty()) {
            tmp = queue.front();
            queue.pop();
            _search_tree[tmp.destination()] = tmp.source();
            // typename Graph_type::adjIterator A(G, e.w);
            for (auto t : _graph.adjacent(tmp.destination())) {
                if (_order[t] == -1) {
                    queue.push(Edge{tmp.destination(), t});
                    _order[t] = _count++;
                }
            }
        }
    }
};

#endif // DERIVED_BFS_IMPROVED_H
