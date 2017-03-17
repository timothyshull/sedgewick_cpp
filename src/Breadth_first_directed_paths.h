#ifndef BREADTH_FIRST_DIRECTED_PATHS_H
#define BREADTH_FIRST_DIRECTED_PATHS_H

#include <limits>
#include <deque>
#include <vector>
#include "Digraph.h"
#include "Stack.h"

class Breadth_first_directed_paths {
public:
    Breadth_first_directed_paths() = default;

    Breadth_first_directed_paths(const Breadth_first_directed_paths&) = default;

    Breadth_first_directed_paths(Breadth_first_directed_paths&&) = default;

    ~Breadth_first_directed_paths() = default;

    Breadth_first_directed_paths& operator=(const Breadth_first_directed_paths&) = default;

    Breadth_first_directed_paths& operator=(Breadth_first_directed_paths&&) = default;

    Breadth_first_directed_paths(Digraph& digraph, int source);

    Breadth_first_directed_paths(Digraph& digraph, std::vector<int>& sources);

    inline bool has_path_to(int v) const { return _marked[v]; }

    inline int distance_to(int v) const { return _distance_to[v]; }

    Stack<int> path_to(int v);

private:
    const static int _infinity = std::numeric_limits<int>::max();
    std::deque<bool> _marked;
    std::vector<int> _edge_to;
    std::vector<int> _distance_to;

    void _bfs(Digraph& digraph, int source);

    void _bfs(Digraph& digraph, std::vector<int>& sources);
};

#endif // BREADTH_FIRST_DIRECTED_PATHS_H
