#ifndef EDGE_WEIGHTED_DIGRAPH_H
#define EDGE_WEIGHTED_DIGRAPH_H

#include <string>
#include <vector>
#include <istream>
#include <sstream>

#include "Directed_edge.h"
#include "In.h"
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

    explicit Edge_weighted_digraph(In<std::ifstream>& in);

    explicit Edge_weighted_digraph(const Edge_weighted_digraph& digraph);

    inline unsigned long num_vertices() const noexcept { return _num_vertices; }

    inline unsigned long num_edges() const noexcept { return _num_edges; }

    void add_edge(Directed_edge& e);

    void add_edge(int source, int destination, double weight);

    std::vector<Directed_edge> adjacent(int vertex) const;

    int outdegree(int vertex) const;

    int indegree(int vertex) const;

    std::vector<Directed_edge> edges() const;

    std::string to_string() const;

private:
    unsigned long _num_vertices;
    unsigned long _num_edges;
    std::vector<std::vector<Directed_edge>> _adjacency_lists;
    std::vector<int> _indegree;

    void _validate_vertex(int vertex) const;
};

std::ostream& operator<<(std::ostream& os, const Edge_weighted_digraph& out);

#endif // EDGE_WEIGHTED_DIGRAPH_H
