#ifndef EULERIAN_CYCLE_H
#define EULERIAN_CYCLE_H

#include <vector>
#include "Graph.h"
#include "Stack.h"

class Edge {
public:
    Edge(int v, int w);
    int other(int vertex);
private:
    const int v;
    const int w;
    bool isUsed;
};

class Eulerian_cycle {
public:
    Eulerian_cycle(Graph& G);

    std::vector<int> cycle();

    bool hasEulerianCycle();

private:
    Stack<int> cycle;

    int nonIsolatedVertex(Graph& G);

    bool hasEulerianCycle(Graph& G);

    bool certifySolution(Graph& G);

    void unitTest(Graph& G, std::string& description);
};

#endif // EULERIAN_CYCLE_H
