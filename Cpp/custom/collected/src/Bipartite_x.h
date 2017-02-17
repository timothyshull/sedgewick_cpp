#ifndef BIPARTITE_X_H
#define BIPARTITE_X_H

#include <deque>
#include <vector>
#include "Queue.h"
#include "Graph.h"

enum class Bipartite_x_color : bool {
    white = false,
    black = true
};

class Bipartite_x {
public:
    Bipartite_x(Graph& graph);

    inline bool is_bipartite() const noexcept { return _is_bipartite; };

    Bipartite_x_color color(int vertex) const;

    inline Queue<int> odd_cycle() const noexcept { return _cycle; }

private:
    bool _is_bipartite;
    std::deque<Bipartite_x_color> _color;
    std::deque<bool> _marked;
    std::vector<int> _edge_to;
    Queue<int> _cycle;

    void _bfs(Graph& graph, int source);

    bool _check(Graph& graph) const;
};

#endif // BIPARTITE_X_H
