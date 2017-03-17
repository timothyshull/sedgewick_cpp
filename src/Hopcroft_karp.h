#ifndef HOPCROFT_KARP_H
#define HOPCROFT_KARP_H

#include <vector>
#include <deque>
#include "Graph.h"
#include "Bipartite_x.h"

class Hopcroft_karp {
public:
    Hopcroft_karp(Graph& G);

    int mate(int v);

    bool is_matched(int v);

    int size();

    bool is_perfect();

    bool in_min_vertex_cover(int v);

    std::string to_string(std::vector<int>& path);

private:
    const static int _unmatched = -1;
    const int _num_vertices;
    Bipartite_x _bipartition;
    int cardinality;
    std::vector<int> _mate;
    std::deque<bool> _in_min_vertex_cover;
    std::deque<bool> _marked;
    std::vector<int> _distance_to;

    bool _is_level_graph_edge(int v, int w);

    bool _is_residual_graph_edge(int v, int w);

    bool _has_augmenting_path(Graph& G);

    void validate(int v);

    bool _certify_solution(Graph& G);
};

std::ostream& operator<<(std::ostream& os, Hopcroft_karp& out);

#endif // HOPCROFT_KARP_H
