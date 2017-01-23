#ifndef DIRECTED_EULERIAN_CYCLE_H
#define DIRECTED_EULERIAN_CYCLE_H

#include <vector>
#include "Stack.h"
#include "Digraph.h"

class Directed_eulerian_cycle {
public:
    Directed_eulerian_cycle(Digraph& G);

    std::vector<int> cycle();

    bool hasEulerianCycle();

private:
    Stack<int> cycle;

    int nonIsolatedVertex(Digraph& G);

    bool hasEulerianCycle(Digraph& G);

    bool certifySolution(Digraph& G);

    void unitTest(Digraph& G, std::string& description);

};

#endif // DIRECTED_EULERIAN_CYCLE_H
