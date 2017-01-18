#ifndef COLLECTED_DIGRAPH_H
#define COLLECTED_DIGRAPH_H

#include <vector>
#include "Bag.h"

class Digraph {
public:
    Digraph() = default;

    Digraph(const Digraph&) = default;

    Digraph(Digraph&&) = default;

    ~Digraph() = default;

    Digraph& operator=(const Digraph&) = default;

    Digraph& operator=(Digraph&&) = default;

    explicit Digraph(int num_vertices);

    explicit Digraph(std::istream in);

    explicit Digraph(Digraph& g);

    inline int num_vertices() const { return _num_vertices; };

    inline int num_edges() const { return _num_edges; };

    void add_edge(int v, int w);

    std::vector<int> adjacent(int v) const;

    int outdegree(int v) const;

    int indegree(int v) const;

    Digraph reverse() const;

    std::string to_string() const;

private:
    int _num_vertices;
    int _num_edges;
    std::vector<std::vector<int>> _adjacency_lists;
    std::vector<int> _indegree;

    void _validate_vertex(int v) const;
};

std::ostream& operator<<(std::ostream& os, const Digraph& out);

#endif //COLLECTED_DIGRAPH_H
