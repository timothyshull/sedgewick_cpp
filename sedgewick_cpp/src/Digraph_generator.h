#ifndef DIGRAPH_GENERATOR_H
#define DIGRAPH_GENERATOR_H

#include "Digraph.h"

class Digraph_generator {
public:
    class Edge {
    public:
        Edge(int v, int w);

        bool operator<(const Edge& rhs) const;

        inline bool operator==(const Edge& rhs) const { return _v == rhs._v && _w == rhs._w; };

    private:
        int _v;
        int _w;
    };

    Digraph_generator() = delete;

    Digraph_generator(const Digraph_generator&) = delete;

    Digraph_generator(Digraph_generator&&) = delete;

    ~Digraph_generator() = delete;

    Digraph_generator& operator=(const Digraph_generator&) = delete;

    Digraph_generator& operator=(Digraph_generator&&) = delete;

    static Digraph simple(int num_vertices, int num_edges);

    static Digraph simple(int num_vertices, double probability);

    static Digraph complete(int num_vertices);

    static Digraph dag(int num_vertices, int num_edges);

    static Digraph tournament(int num_vertices);

    static Digraph rooted_in_dag(int num_vertices, int num_edges);

    static Digraph rooted_out_dag(int num_vertices, int num_edges);

    static Digraph rooted_in_tree(int num_vertices);

    static Digraph rooted_out_tree(int num_vertices);

    static Digraph path(int num_vertices);

    static Digraph binary_tree(int num_vertices);

    static Digraph cycle(int num_vertices);

    static Digraph eulerian_cycle(int num_vertices, int num_edges);

    static Digraph eulerian_path(int num_vertices, int num_edges);

    static Digraph strong(int num_vertices, int num_edges, int c);

private:
    static void _check_vertices_and_edges(int num_vertices, int num_edges);
};

#endif // DIGRAPH_GENERATOR_H
