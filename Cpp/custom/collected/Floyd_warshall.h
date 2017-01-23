#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include <vector>
#include "Directed_edge.h"
#include "Adj_matrix_edge_weighted_digraph.h"

class Floyd_warshall {
public:
    Floyd_warshall(Adj_matrix_edge_weighted_digraph& G);
    bool hasNegativeCycle();
    std::vector<Directed_edge> negativeCycle();
    bool hasPath(int s, int t);
    double dist(int s, int t);
    std::vector<Directed_edge> path(int s, int t);

private:
    bool hasNegativeCycle;
    std::vector<std::vector<double>> distTo;
    std::vector<std::vector<Directed_edge>> edgeTo;

    bool check(Adj_matrix_edge_weighted_digraph& G);
};

#endif // FLOYD_WARSHALL_H
