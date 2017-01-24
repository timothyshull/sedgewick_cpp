#ifndef DIGRAPH_GENERATOR_H
#define DIGRAPH_GENERATOR_H

#include "Digraph.h"

namespace Digraph_generator {
    class Edge {
    public:
        Edge(int v, int w);

        bool operator<(Edge& rhs);

    private:
        int v;
        int w;
    };

    Digraph simple(int V, int E);

    Digraph simple(int V, double p);

    Digraph complete(int V);

    Digraph dag(int V, int E);

    Digraph tournament(int V);

    Digraph rooted_in_dag(int V, int E);

    Digraph rooted_out_dag(int V, int E);

    Digraph rooted_in_tree(int V);

    Digraph rooted_out_tree(int V);

    Digraph path(int V);

    Digraph binary_tree(int V);

    Digraph cycle(int V);

    Digraph eulerian_cycle(int V, int E);

    Digraph eulerian_path(int V, int E);

    Digraph strong(int V, int E, int c);
};

#endif // DIGRAPH_GENERATOR_H
