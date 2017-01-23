#ifndef EDGE_WEIGHTED_GRAPH_H
#define EDGE_WEIGHTED_GRAPH_H

#include <vector>
#include "Edge.h"
#include "In.h"

class Edge_weighted_graph {
public:
    Edge_weighted_graph(int V);
    Edge_weighted_graph(int V, int E);
    Edge_weighted_graph(In& in);
    Edge_weighted_graph(Edge_weighted_graph& G);
    int V();
    int E();
    void addEdge(Edge& e);
    std::vector<Edge> adj(int v);
    int degree(int v);
    std::vector<Edge> edges();
    std::string toString();
private:
    const int V;
    int E;
    std::vector<std::vector<Edge>> adj;
void validateVertex(int v);
};

std::ostream& operator<<(std::ostream& os, Edge_weighted_graph& out);

#endif // EDGE_WEIGHTED_GRAPH_H
