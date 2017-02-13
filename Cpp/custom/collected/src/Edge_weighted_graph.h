#ifndef EDGE_WEIGHTED_GRAPH_H
#define EDGE_WEIGHTED_GRAPH_H

#include <vector>
#include "Edge.h"
#include "In.h"

class Edge_weighted_graph {
public:
    Edge_weighted_graph(int num_vertices);

    Edge_weighted_graph(int num_vertices, int num_edges);

    Edge_weighted_graph(In& in);

    Edge_weighted_graph(Edge_weighted_graph& graph);

    inline unsigned long num_vertices() const noexcept { return _num_vertices; }

    inline unsigned long num_edges() const noexcept { return _num_edges; }

    void add_edge(Edge& edge);

    void add_edge(int v, int w, double weight);

    std::vector<Edge> adjacent(int vertex);

    int degree(int v);

    std::vector<Edge> edges();

    std::string to_string();

private:
    const unsigned long _num_vertices;
    unsigned long _num_edges;
    std::vector<std::vector<Edge>> _adjacency_lists;

    void _validate_vertex(int vertex);
};

std::ostream& operator<<(std::ostream& os, Edge_weighted_graph& out);

#endif // EDGE_WEIGHTED_GRAPH_H
