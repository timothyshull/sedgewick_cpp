// Program 18.2 - Graph search
#ifndef GENERALIZED_GRAPH_SEARCH_H
#define GENERALIZED_GRAPH_SEARCH_H

#include <vector>

#include "Edge.h"

template<typename Graph_type>
class Generalized_graph_search {
protected:
public:
    Generalized_graph_search(const Graph_type& graph) : _graph{graph}, _order(graph.num_vertices(), -1), _count{0} {}

    inline int operator[](int v) const { return _order[v]; }
protected:
    const Graph_type& _graph;
    int _count;
    std::vector<int> _order;

    // virtual void _search_c(Edge&) = 0;

    virtual void _search_c(Edge&&) = 0; // called once for each component

    void _search()
    {
        for (int v{0}; v < _graph.num_vertices(); ++v) {
            if (_order[v] == -1) { _search_c(Edge(v, v)); }
        }
    }
};



#endif // GENERALIZED_GRAPH_SEARCH_H
