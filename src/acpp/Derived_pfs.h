// Program 18.10 - Generalized graph search (program is misnamed)
#ifndef DERIVED_PFS_H
#define DERIVED_PFS_H

#include "Random_queue.h"
#include "Generalized_graph_search.h"

template<typename Graph_type>
class Derived_pfs : public Generalized_graph_search<Graph_type> {
public:
    Derived_pfs(Graph_type& graph)
            : Generalized_graph_search<Graph_type>(graph),
              _search_tree(graph.V(), -1) { _search(); }

    inline int search_tree(int v) const { return _search_tree[v]; }

private:
    std::vector<int> _search_tree;

    void _search_c(Edge&& e)
    {
        Random_queue<Edge> queue{_graph.num_vertices()};
        queue.put(e);
        _order[e.destination()] = _count++;
        Edge tmp;
        while (!queue.empty()) {
            tmp = queue.get();
            _search_tree[e.destination()] = e.source();
            // typename Graph_type::adjIterator A(G, e.w);
            for (auto t : _graph.adjacent(e.destination())) {
                if (_order[t] == -1) {
                    queue.put(Edge(e.destination(), t));
                    _order[t] = _count++;
                } else if (_search_tree[t] == -1) { queue.update(Edge{e.destination(), t}); }
            }
        }
    }
};

#endif // DERIVED_PFS_H
