#ifndef BREADTH_FIRST_DIRECTED_PATHS_H
#define BREADTH_FIRST_DIRECTED_PATHS_H

#include <limits>
#include <deque>
#include <vector>
#include "Digraph.h"

class Breadth_first_directed_paths {
public:
    Breadth_first_directed_paths(Digraph& G, int s);
    Breadth_first_directed_paths(Digraph& G, std::vector<int>& sources);
    bool hasPathTo(int v);
    int distTo(int v);
    std::vector<int> pathTo(int v);
private:
    const static int INFINITY = std::numeric_limits<int>::max();
    std::deque<bool> marked;
    std::vector<int> edgeTo;
    std::vector<int> distTo;

    void bfs(Digraph& G, int s);
    void bfs(Digraph& G, std::vector<int>& sources);
};

#endif // BREADTH_FIRST_DIRECTED_PATHS_H
