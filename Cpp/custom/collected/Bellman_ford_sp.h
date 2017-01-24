#ifndef BELLMAN_FORD_SP_H
#define BELLMAN_FORD_SP_H

#include <deque>
#include "Edge_weighted_digraph.h"
#include "Queue.h"

class Bellman_ford_sp {
public:
    Bellman_ford_sp(Edge_weighted_digraph, int);

    bool hasNegativeCycle();

    std::vector<Directed_edge> negativeCycle();

    double distance_to(int);

    bool has_path_to(int);

    std::vector<Directed_edge> path_to(int);

private:
    std::vector<double> distance_to;
    std::vector<Directed_edge> edgeTo;
    std::deque<bool> onQueue;
    Queue<int> queue;
    int cost;
    std::vector<Directed_edge> cycle;

    void relax(Edge_weighted_digraph, int);

    void findNegativeCycle();
    bool check(Edge_weighted_digraph, int);
};

#endif // BELLMAN_FORD_SP_H
