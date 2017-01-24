#ifndef TOPOLOGICAL_X_H
#define TOPOLOGICAL_X_H

#include <vector>
#include "Queue.h"
#include "Digraph.h"
#include "Edge_weighted_digraph.h"

class Topological_x {
public:
    Topological_x(Digraph& G);
    Topological_x(Edge_weighted_digraph& G);

    inline std::vector<int> order();

    inline bool has_order();

    int rank(int v);
private:
    Queue<int> order;
    std::vector<int> rank;

    bool check(Digraph& G);
    bool check(Edge_weighted_digraph& G);
    void validateVertex(int v);
};

#endif // TOPOLOGICAL_X_H
