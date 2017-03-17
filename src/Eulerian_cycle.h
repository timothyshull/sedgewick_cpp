#ifndef EULERIAN_CYCLE_H
#define EULERIAN_CYCLE_H

#include <vector>
#include "Graph.h"
#include "Stack.h"

class Eulerian_cycle {
private:
    class Edge {
    public:
        Edge(int v, int w);

        int other(int vertex);

    private:
        const int _v;
        const int _w;
        bool _is_used;

        friend class Eulerian_cycle;
    };

public:
    Eulerian_cycle(Graph& graph);

    inline Stack<int> cycle() const { return _cycle; }

    inline bool has_eulerian_cycle() const { return !_cycle.is_empty(); }

    // make accessible from main
    static void unit_test(Graph& graph, std::string&& description);

private:
    Stack<int> _cycle;

    int _non_isolated_vertex(Graph& graph);

    bool _has_eulerian_cycle(Graph& graph);

    bool _certify_solution(Graph& graph);
};

#endif // EULERIAN_CYCLE_H
