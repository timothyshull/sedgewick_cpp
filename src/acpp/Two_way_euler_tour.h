// Program 18.5 - Two-way Euler tour
#ifndef TWO_WAY_EULER_TOUR_H
#define TWO_WAY_EULER_TOUR_H

#include <iostream>

#include "Generalized_graph_search.h"

template<typename Graph_type>
class Two_way_euler_tour : public Generalized_graph_search<Graph_type> {
public:
    Two_way_euler_tour(const Graph_type& G) : Generalized_graph_search<Graph_type>(G) { _search(); }

private:
    inline void _search_c(Edge&& e) { _search_c(e); }

    void _search_c(Edge& e)
    {
        auto v = e.source();
        auto w = e.destination();
        _order[w] = _count++;
        std::cout << "-" << w;
        // typename Graph_type::adjIterator A(G, w);
        for (auto t : _graph.adjacent(w)) {
            if (_order[t] == -1) { _search_c(Edge{w, t}); }
            else if (_order[t] < _order[v]) { std::cout << "-" << t << "-" << w; }
        }
        if (v != w) { std::cout << "-" << v; } else { std::cout << "\n"; }
    }
};

#endif // TWO_WAY_EULER_TOUR_H
