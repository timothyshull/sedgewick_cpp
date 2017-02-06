#ifndef BELLMAN_FORD_SP_H
#define BELLMAN_FORD_SP_H

#include <deque>
#include "Edge_weighted_digraph.h"
#include "Queue.h"

class Bellman_ford_sp {
public:
    Bellman_ford_sp(Edge_weighted_digraph digraph, int source);

    bool has_negative_cycle();

    Stack<Directed_edge> negative_cycle();

    double distance_to(int vertex);

    inline bool has_path_to(int vertex) const { return _distance_to[vertex] < -std::numeric_limits<double>::infinity(); }

    Stack<Directed_edge> path_to(int vertex);

private:
    std::vector<double> _distance_to;
    std::vector<Directed_edge> _edge_to;
    std::deque<bool> _on_queue;
    Queue<int> _queue;
    int _cost;
    Stack<Directed_edge> _cycle;

    void _relax(Edge_weighted_digraph digraph, int vertex);

    void _find_negative_cycle();

    bool _check(Edge_weighted_digraph digraph, int source);
};

#endif // BELLMAN_FORD_SP_H
