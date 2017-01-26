#ifndef BREADTH_FIRST_PATHS_H
#define BREADTH_FIRST_PATHS_H

#include <vector>
#include <deque>
#include "Graph.h"
#include "Stack.h"

class Breadth_first_paths {
public:
    Breadth_first_paths() = default;

    Breadth_first_paths(const Breadth_first_paths&) = default;

    Breadth_first_paths(Breadth_first_paths&&) = default;

    ~Breadth_first_paths() = default;

    Breadth_first_paths& operator=(const Breadth_first_paths&) = default;

    Breadth_first_paths& operator=(Breadth_first_paths&&) = default;

    Breadth_first_paths(Graph& graph, int source);

    Breadth_first_paths(Graph& graph, std::vector<int>& sources);

    inline bool has_path_to(int v) const { return _marked[v]; }

    inline int distance_to(int v) { return _distance_to[v]; }

    Stack<int> path_to(int v);

private:
    const static int _infinity = std::numeric_limits<int>::max();
    std::deque<bool> _marked;
    std::vector<int> _edge_to;
    std::vector<int> _distance_to;

    void _bfs(Graph& graph, int source);

    void _bfs(Graph& graph, std::vector<int>& sources);

    bool _check(Graph& graph, int source);

};

#endif // BREADTH_FIRST_PATHS_H
