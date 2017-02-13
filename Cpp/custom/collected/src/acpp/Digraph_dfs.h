#ifndef DIGRAPH_DFS_H
#define DIGRAPH_DFS_H

#include <vector>
#include <iostream>

#include "Edge.h"

template<typename Graph_type>
class Digraph_dfs {
public:
    Digraph_dfs(const Graph_type& graph)
            : _graph{graph},
              _count{0},
              cntP{0},
              _preorder(graph.num_vertices(), -1),
              _postorder(graph.num_vertices(), -1)
    {
        for (int v{0}; v < graph.num_vertices(); ++v) {
            if (_preorder[v] == -1) { _dfs_r(Edge(v, v)); }
        }
    }

private:
    const Graph_type& _graph;
    int _depth;
    int _count;
    int cntP;
    std::vector<int> _preorder;
    std::vector<int> _postorder;

    void show(std::string&& s, Edge& e)
    {
        for (int i = 0; i < _depth; ++i) { std::cout << "  "; }
        std::cout << e.source() << "-" << e.destination() << s << "\n";
    }

    void _dfs_r(Edge& e)
    {
        int w{e.destination()};
        show(" tree", e);
        _preorder[w] = _count++;
        ++_depth;
        // typename Graph_type::adjIterator A(_graph, w);
        for (auto t : _graph.adjacent(w)) {
            Edge x{w, t};
            if (_preorder[t] == -1) { _dfs_r(x); }
            else if (_postorder[t] == -1) { show(" back", x); }
            else if (_preorder[t] > _preorder[w]) { show(" down", x); }
            else { show(" cross", x); }
        }
        _postorder[w] = cntP++;
        --_depth;
    }
};



#endif // DIGRAPH_DFS_H
