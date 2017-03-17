#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <vector>

#include "Bag.h"
#include "In.h"

class Digraph {
private:
    std::size_t _num_vertices;
    std::size_t _num_edges;
    std::vector<std::vector<int>> _adjacency_lists;
    std::vector<int> _indegree;

public:
    Digraph() = default;

    Digraph(const Digraph&) = default;

    Digraph(Digraph&&) = default;

    ~Digraph() = default;

    Digraph& operator=(const Digraph&) = default;

    Digraph& operator=(Digraph&&) = default;

    explicit Digraph(std::size_t num_vertices);

    explicit Digraph(In<std::ifstream>& in);

    explicit Digraph(Digraph& digraph);

    inline std::size_t num_vertices() const noexcept { return _num_vertices; };

    inline std::size_t num_edges() const noexcept { return _num_edges; };

    void add_edge(int v, int w);

    std::vector<int> adjacent(int v) const;

    int outdegree(int v) const;

    int indegree(int v) const;

    Digraph reverse() const;

    std::string to_string() const;

private:
    void _validate_vertex(int v) const;

};

inline std::ostream& operator<<(std::ostream& os, const Digraph& out) { return os << out.to_string(); }

#endif // DIGRAPH_H
