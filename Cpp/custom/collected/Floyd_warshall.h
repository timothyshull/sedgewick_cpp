#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include <vector>
#include "Directed_edge.h"
#include "Adj_matrix_edge_weighted_digraph.h"

class Floyd_warshall {
public:


    Floyd_warshall(Adj_matrix_edge_weighted_digraph& digraph);

    inline bool has_negative_cycle() const noexcept { return _has_negative_cycle; }

    std::vector<Directed_edge> negative_cycle();

    inline bool has_path(int source, int dest) const { return _distances[source][dest] < std::numeric_limits<double>::infinity(); }

    double distance(int s, int t);

    std::vector<Directed_edge> path(int source, int dest);

private:
    bool _has_negative_cycle;
    std::vector<std::vector<double>> _distances;
    std::vector<std::vector<Directed_edge>> _edge_to;

    bool _check(Adj_matrix_edge_weighted_digraph& digraph);
};

#endif // FLOYD_WARSHALL_H
