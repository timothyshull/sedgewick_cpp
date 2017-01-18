#ifndef EDGE_WEIGHTED_DIGRAPH_H
#define EDGE_WEIGHTED_DIGRAPH_H

#include <string>
#include <vector>
#include <istream>
#include <sstream>

#include "Directed_edge.h"
#include "Std_random.h"
#include "Stack.h"

class Edge_weighted_digraph {
public:
    Edge_weighted_digraph() = default;

    Edge_weighted_digraph(Edge_weighted_digraph&&) = default;

    ~Edge_weighted_digraph() = default;

    Edge_weighted_digraph& operator=(const Edge_weighted_digraph&) = default;

    Edge_weighted_digraph& operator=(Edge_weighted_digraph&&) = default;

    explicit Edge_weighted_digraph(int num_vertices);

    Edge_weighted_digraph(int num_vertices, int num_edges);

    explicit Edge_weighted_digraph(std::istream& in);

    explicit Edge_weighted_digraph(const Edge_weighted_digraph& g);

    inline int num_vertices() const { return _num_vertices; }

    inline int num_edges() const { return _num_edges; }

    void add_edge(Directed_edge& e);

    void add_edge(int source, int destination, double weight);

    std::vector<Directed_edge> adjacent(int v) const;

    int outdegree(int v) const;

    int indegree(int v) const;

    std::vector<Directed_edge> edges() const;

    std::string to_string() const;

private:
    int _num_vertices;
    int _num_edges;
    std::vector<std::vector<Directed_edge>> _adjacency_lists;
    std::vector<int> _indegree;

    void _validate_vertex(int v) const;
};

std::ostream& operator<<(std::ostream& os, const Edge_weighted_digraph& out);

#endif // EDGE_WEIGHTED_DIGRAPH_H
