#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include "Graph.h"

namespace Graph_generator {
    class Edge {
    public:
        Edge() = default;

        Edge(const Edge&) = default;

        Edge(Edge&&) = default;

        Edge(const Edge&) = default;

        ~Edge() = default;

        Edge& operator=(const Edge&) = default;

        Edge& operator=(Edge&&) = default;

        Edge(int v, int w);

        bool operator<(Edge& rhs);

    private:
        int _v;
        int _w;
    };

    Graph simple(int num_vertices, int num_edges);

    Graph simple(int num_vertices, double probability);

    Graph complete(int num_vertices);

    Graph complete_bipartite(int v1, int v2);

    Graph bipartite(int v1, int v2, int num_edges);

    Graph bipartite(int v1, int v2, double probability);

    Graph path(int num_vertices);

    Graph binary_tree(int num_vertices);

    Graph cycle(int num_vertices);

    Graph eulerian_cycle(int num_vertices, int num_edges);

    Graph eulerian_path(int num_vertices, int num_edges);

    Graph wheel(int num_vertices);

    Graph star(int V);

    Graph regular(int num_vertices, int k);

    Graph tree(int num_vertices);
};

#endif // GRAPH_GENERATOR_H
