#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

#include "In.h"

class Graph {
public:
    Graph() = default;

    Graph(const Graph&) = default;

    Graph(Graph&&) = default;

    ~Graph() = default;

    Graph& operator=(const Graph&) = default;

    Graph& operator=(Graph&&) = default;

    explicit Graph(int v);

    explicit Graph(In& in);

    Graph(const Graph& g);

    inline unsigned long num_vertices() const noexcept { return _num_vertices; }

    inline unsigned long num_edges() const noexcept { return _num_edges; }

    void add_edge(int v, int w);

    std::vector<int> adjacent(int v) const;

    int degree(int v) const;

    std::string to_string() const;

private:
    unsigned long _num_vertices;
    unsigned long _num_edges;
    std::vector<std::vector<int>> _adjacency_lists;

    void _validate_vertex(int v) const;
};

std::ostream& operator<<(std::ostream& os, const Graph& out);

#endif // GRAPH_H
