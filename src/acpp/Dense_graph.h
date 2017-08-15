#ifndef DENSE_GRAPH_H
#define DENSE_GRAPH_H

#include <vector>

#include "Edge.h"

class Dense_graph_iterator {
    const Dense_graph& _graph;
    int i;
    int _vertex;
public:
    Dense_graph_iterator(const Dense_graph& graph, int vertex) : _graph{graph}, _vertex{vertex}, i{-1} {}

    int begin()
    {
        i = -1;
        return next();
    }

    int next()
    {
        for (++i; i < _graph.num_vertices(); ++i) {
            if (_graph._adjacency_matrix[_vertex][i] == true) { return i; }
        }
        return -1;
    }

    bool end() { return i >= _graph.num_vertices(); }
};

class Dense_graph {
public:
    Dense_graph(int num_vertices, bool digraph = false)
            : _adjacency_matrix(num_vertices),
              _num_vertices(num_vertices),
              _num_edges(0),
              _is_directed(digraph)
    {
        for (auto i = 0; i < num_vertices; ++i) {
            _adjacency_matrix[i].assign(num_vertices, false);
        }
    }

    inline int num_vertices() const noexcept { return _num_vertices; }

    inline int num_edges() const noexcept { return _num_edges; }

    inline bool directed() const { return _is_directed; }

    void insert(Edge& e)
    {
        auto v = e.source();
        auto w = e.destination();
        if (_adjacency_matrix[v][w] == false) { _num_edges++; }
        _adjacency_matrix[v][w] = true;
        if (!_is_directed) { _adjacency_matrix[w][v] = true; }
    }

    void remove(Edge& e)
    {
        auto v = e.source();
        auto w = e.destination();
        if (_adjacency_matrix[v][w] == true) { --_num_edges; }
        _adjacency_matrix[v][w] = false;
        if (!_is_directed) { _adjacency_matrix[w][v] = false; }
    }

    bool edge(int v, int w) const { return _adjacency_matrix[v][w]; }

    friend class Dense_graph_iterator;

private:
    int _num_vertices;
    int _num_edges;
    bool _is_directed;
    std::vector<std::vector<bool>> _adjacency_matrix;
};

#endif // DENSE_GRAPH_H
