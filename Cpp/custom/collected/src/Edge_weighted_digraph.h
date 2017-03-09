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
private:
    std::size_t _num_vertices;
    std::size_t _num_edges;
    std::vector<std::vector<Directed_edge>> _adjacency_lists;
    std::vector<int> _indegree;

public:
    Edge_weighted_digraph() = default;

    Edge_weighted_digraph(Edge_weighted_digraph&&) = default;

    ~Edge_weighted_digraph() = default;

    Edge_weighted_digraph& operator=(const Edge_weighted_digraph&) = default;

    Edge_weighted_digraph& operator=(Edge_weighted_digraph&&) = default;

    explicit Edge_weighted_digraph(std::size_t num_vertices);

    Edge_weighted_digraph(std::size_t num_vertices, std::size_t num_edges);

    explicit Edge_weighted_digraph(In<std::ifstream>& in);

    explicit Edge_weighted_digraph(const Edge_weighted_digraph& digraph);

    inline std::size_t num_vertices() const noexcept { return _num_vertices; }

    inline std::size_t num_edges() const noexcept { return _num_edges; }

    void add_edge(Directed_edge& e);

    void add_edge(int source, int destination, double weight);

    std::vector<Directed_edge> adjacent(int vertex) const;

    int outdegree(int vertex) const;

    int indegree(int vertex) const;

    std::vector<Directed_edge> edges() const;

    std::string to_string() const;

private:
    void _validate_vertex(int vertex) const;

};

inline std::ostream& operator<<(std::ostream& os, const Edge_weighted_digraph& out) { return os << out.to_string(); }

#endif // EDGE_WEIGHTED_DIGRAPH_H
