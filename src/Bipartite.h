#ifndef BIPARTITE_H
#define BIPARTITE_H

#include <deque>
#include <vector>
#include "Stack.h"
#include "Graph.h"

class Bipartite {
public:
    Bipartite(Graph& graph);

    inline bool is_bipartite() const noexcept { return _is_bipartite; }

    bool color(int vertex) const;

    inline Stack<int> odd_cycle() const noexcept { return _cycle; };

private:
    bool _is_bipartite;
    std::deque<bool> _color;
    std::deque<bool> _marked;
    std::vector<int> _edge_to;
    Stack<int> _cycle;

    void _dfs(Graph& graph, int vertex);

    bool _check(Graph& graph) const;
};

#endif // BIPARTITE_H
