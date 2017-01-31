#ifndef DIRECTED_EULERIAN_CYCLE_H
#define DIRECTED_EULERIAN_CYCLE_H

#include <vector>
#include "Stack.h"
#include "Digraph.h"

class Directed_eulerian_cycle {
public:
    Directed_eulerian_cycle(Digraph& digraph);

    inline Stack<int> cycle() const { return _cycle; }

    inline bool has_eulerian_cycle() { return !_cycle.is_empty(); }

    // made public to allow running in main
    static void unit_test(Digraph& digraph, std::string&& description);
private:
    Stack<int> _cycle;

    int _non_isolated_vertex(Digraph& digraph);

    bool _has_eulerian_cycle(Digraph& digraph);

    bool _certify_solution(Digraph& digraph);

};

#endif // DIRECTED_EULERIAN_CYCLE_H
