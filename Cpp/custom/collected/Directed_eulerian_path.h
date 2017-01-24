#ifndef DIRECTED_EULERIAN_PATH_H
#define DIRECTED_EULERIAN_PATH_H

#include "Stack.h"
#include "Digraph.h"

class Directed_eulerian_path {
public:
    Directed_eulerian_path(Digraph& G);

    std::vector<int> path();

    bool hasEulerianPath();

private:
    Stack<int> path;

    int nonIsolatedVertex(Digraph& G);

    bool hasEulerianPath(Digraph& G);

    bool check(Digraph& G);

    void unit_test(Digraph& G, std::string& description);
};

#endif // DIRECTED_EULERIAN_PATH_H
