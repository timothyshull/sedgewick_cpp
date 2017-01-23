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

    Digraph rootedInDAG(int V, int E);

    Digraph rootedOutDAG(int V, int E);

    Digraph rootedInTree(int V);

    Digraph rootedOutTree(int V);

    Digraph path(int V);

    Digraph binaryTree(int V);

    Digraph cycle(int V);

    Digraph eulerianCycle(int V, int E);

    Digraph eulerianPath(int V, int E);

    Digraph strong(int V, int E, int c);
};

#endif // DIGRAPH_GENERATOR_H
