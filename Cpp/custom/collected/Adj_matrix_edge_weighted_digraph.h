#ifndef ADJ_MATRIX_EDGE_WEIGHTED_DIGRAPH_H
#define ADJ_MATRIX_EDGE_WEIGHTED_DIGRAPH_H

#include <vector>
#include <memory>

#include "Directed_edge.h"

class Adj_matrix_edge_weighted_digraph;

using Directed_edge_owning_pointer = std::unique_ptr<Directed_edge>;
using Directed_edge_raw_pointer = Directed_edge*;

class Adj_iterator {
private:
    // to allow -1
    int _v;
    int _w;
    Adj_matrix_edge_weighted_digraph& _graph;

public:
    using iterator_category = std::random_access_iterator_tag;
    using Value_type = Directed_edge_raw_pointer;
    using Reference_type = Value_type&;

    inline Adj_iterator() = delete;

    inline explicit Adj_iterator(Adj_matrix_edge_weighted_digraph& g) noexcept;

    inline Adj_iterator(Adj_matrix_edge_weighted_digraph& g, int v) noexcept;

    inline Adj_iterator(Adj_matrix_edge_weighted_digraph& g, int v, int w) noexcept;

    inline Value_type operator*() const;

    inline Value_type operator->() const;

    inline Adj_iterator& operator++();

    inline Adj_iterator operator++(int);

    inline Adj_iterator& operator--();

    inline Adj_iterator operator--(int);

    std::vector<Directed_edge_owning_pointer>& operator[](const int& index);

    friend
    bool operator==(const Adj_iterator& x, const Adj_iterator& y);

    friend
    bool operator!=(const Adj_iterator& x, const Adj_iterator& y);
};

class Adj_matrix_edge_weighted_digraph {
public:
    using Iterator_type = Adj_iterator;

    explicit Adj_matrix_edge_weighted_digraph(unsigned num_vertices);

    Adj_matrix_edge_weighted_digraph(unsigned num_vertices, unsigned num_edges);

    void add_edge(Directed_edge& e);

    void add_edge(int v, int w, double weight);

    inline unsigned num_vertices() const;

    inline unsigned num_edges() const;

    inline Iterator_type begin() noexcept;

    inline Iterator_type end() noexcept;

    friend
    bool operator==(const Adj_matrix_edge_weighted_digraph& x, const Adj_matrix_edge_weighted_digraph& y);

    friend
    bool operator!=(const Adj_matrix_edge_weighted_digraph& x, const Adj_matrix_edge_weighted_digraph& y);

    std::string to_string() const;

private:
    unsigned _num_vertices;
    unsigned _num_edges;
    std::vector<std::vector<Directed_edge_owning_pointer>> _adjacency_matrix;

    void _check_vertex(int v);

    friend class Adj_iterator;
};

std::ostream& operator<<(std::ostream& os, const Adj_matrix_edge_weighted_digraph& out);

#endif // ADJ_MATRIX_EDGE_WEIGHTED_DIGRAPH_H
