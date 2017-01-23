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

    double distTo(int);

    bool hasPathTo(int);

    std::vector<Directed_edge> pathTo(int);

private:
    std::vector<double> distTo;
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
