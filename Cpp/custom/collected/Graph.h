#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph {
public:
    Graph() = default;

    Graph(const Graph&) = default;

    Graph(Graph&&) = default;

    ~Graph() = default;

    Graph& operator=(const Graph&) = default;

    Graph& operator=(Graph&&) = default;

    explicit Graph(int v);

    explicit Graph(std::istream& in);

    Graph(const Graph& g);

    inline int num_vertices() const { return _num_vertices; }

    inline int num_edges() const { return _num_edges; }

    void add_edge(int v, int w);

    std::vector<int> adjacent(int v) const;

    int degree(int v) const;

    std::string to_string() const;

private:
    int _num_vertices;
    int _num_edges;
    std::vector<std::vector<int>> _adjacency_lists;

    void _validate_vertex(int v) const;
};

std::ostream& operator<<(std::ostream& os, const Graph& out);

#endif // GRAPH_H
