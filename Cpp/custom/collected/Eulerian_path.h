#ifndef EULERIAN_PATH_H
#define EULERIAN_PATH_H

#include <vector>
#include "Stack.h"
#include "Graph.h"A

class Eulerian_path {
private:
    class Edge {
    public:
        Edge(int v, int w);

        int other(int vertex);

    private:
        const int _v;
        const int _w;
        bool _is_used;

        friend class Eulerian_path;
    };

public:
    Eulerian_path(Graph& graph);

    inline Stack<int> path() const { return _path; }

    inline bool has_eulerian_path() const { return !_path.is_empty(); }

    // make available in main
    static void unit_test(Graph& graph, std::string&& description);

private:
    Stack<int> _path;

    int _non_isolated_vertex(Graph& graph);

    bool _has_eulerian_path(Graph& graph);

    bool _certify_solution(Graph& graph);
};

#endif // EULERIAN_PATH_H
