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
    bool has_path_to(int v);
    int distance_to(int v);
    std::vector<int> path_to(int v);
private:
    const static int INFINITY = std::numeric_limits<int>::max();
    std::deque<bool> marked;
    std::vector<int> edgeTo;
    std::vector<int> distance_to;

    void bfs(Digraph& G, int s);
    void bfs(Digraph& G, std::vector<int>& sources);
};

#endif // BREADTH_FIRST_DIRECTED_PATHS_H
