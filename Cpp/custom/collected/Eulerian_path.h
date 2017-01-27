#ifndef EULERIAN_PATH_H
#define EULERIAN_PATH_H

#include <vector>
#include "Stack.h"
#include "Graph.h"A

class Edge {
public:
    Edge(int v, int w);
    int other(int vertex);
private:
    const int _v;
    const int _w;
    bool isUsed;
};

class Eulerian_path {
public:
    Eulerian_path(Graph& G);

    std::vector<int> path();

    bool hasEulerianPath();

private:
    Stack<int> path;

    int nonIsolatedVertex(Graph& G);

    bool hasEulerianPath(Graph& G);

    bool ceertifySolution(Graph& G);

    void unit_test(Graph& G, std::string& description);

};

#endif // EULERIAN_PATH_H
