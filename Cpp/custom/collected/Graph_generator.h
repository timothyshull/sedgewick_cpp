#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include "Graph.h"

namespace Graph_generator {
    class Edge {
    public:
        Edge(int v, int w);

        bool operator<(Edge& rhs);

    private:
        int v;
        int w;
    };

    Graph simple(int V, int E);

    Graph simple(int V, double p);

    Graph complete(int V);

    Graph complete_bipartite(int V1, int V2);

    Graph bipartite(int V1, int V2, int E);

    Graph bipartite(int V1, int V2, double p);

    Graph path(int V);

    Graph binary_tree(int V);

    Graph cycle(int V);

    Graph eulerian_cycle(int V, int E);

    Graph eulerian_path(int V, int E);

    Graph wheel(int V);

    Graph star(int V);

    Graph regular(int V, int k);

    Graph tree(int V);
};

#endif // GRAPH_GENERATOR_H
