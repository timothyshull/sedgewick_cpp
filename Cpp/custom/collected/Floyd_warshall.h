#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include <vector>
#include "Directed_edge.h"
#include "Adj_matrix_edge_weighted_digraph.h"

class Floyd_warshall {
public:
    Floyd_warshall(Adj_matrix_edge_weighted_digraph& G);

    bool has_negative_cycle();

    std::vector<Directed_edge> negative_cycle();

    bool has_path(int s, int t);

    double distance(int s, int t);

    std::vector<Directed_edge> path(int s, int t);

private:
    bool _has_negative_cycle;
    std::vector<std::vector<double>> _distances;
    std::vector<std::vector<Directed_edge>> _edge_to;

    bool check(Adj_matrix_edge_weighted_digraph& G);
};

#endif // FLOYD_WARSHALL_H
