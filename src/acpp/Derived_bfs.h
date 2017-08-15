#ifndef DERIVED_BFS_H
#define DERIVED_BFS_H

#include <queue>

#include "Generalized_graph_search.h"

template<typename Graph_type>
class Derived_bfs : public Generalized_graph_search<Graph_type> {
public:
    Derived_bfs(Graph_type& graph) : Generalized_graph_search<Graph_type>{graph}, _search_tree(graph.num_vertices(), -1) { _search(); }

    int search_tree(int v) const { return _search_tree[v]; }

private:
    std::vector<int> _search_tree;

    void _search_c(Edge&& e)
    {
        std::queue<Edge> queue;
        queue.push(e);
        Edge tmp;
        while (!queue.empty()) {
            tmp = queue.front();
            queue.pop();
            if (_order[tmp.destination()] == -1) {
                auto v = e.source();
                auto w = e.destination();
                _order[w] = _count++;
                _search_tree[w] = v;
                // typename Graph_type::adjIterator A(G, w);
                for (auto t : _graph.adjacent(w)) {
                    if (_order[t] == -1) { queue.push(Edge(w, t)); }
                }
            }
        }
    }
};

#endif // DERIVED_BFS_H
