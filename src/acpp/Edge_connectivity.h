// Program 18.7 - Edge connectivity
#ifndef EDGE_CONNECTIVITY_H
#define EDGE_CONNECTIVITY_H

#include "Generalized_graph_search.h"

template<typename Graph_type>
class Edge_connectivity : public Generalized_graph_search<Graph_type> {
public:
    Edge_connectivity(const Graph_type& graph)
            : Generalized_graph_search<Graph_type>(graph),
              _b_count(0),
              _low(graph.V(), -1) { _search(); }

    int count() const { return _b_count + 1; }

private:
    int _b_count;
    std::vector<int> _low;

    void _search_c(Edge&& e)
    {
        int w{e.destination()};
        _order[w] = _count++;
        _low[w] = _order[w];
        // typename Graph_type::adjIterator A(G, w);
        for (auto t : _graph.adjacent(w)) {
            if (_order[t] == -1) {
                _search_c(Edge{w, t});
                if (_low[w] > _low[t]) { _low[w] = _low[t]; }
                if (_low[t] == _order[t]) {
                    ++_b_count;
                } // w-t is a bridge
            } else if (t != e.source()) {
                if (_low[w] > _order[t]) { _low[w] = _order[t]; }
            }
        }
    }
};

#endif // EDGE_CONNECTIVITY_H
