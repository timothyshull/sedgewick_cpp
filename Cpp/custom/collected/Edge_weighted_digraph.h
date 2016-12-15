#ifndef COLLECTED_EDGE_WEIGHTED_DIGRAPH_H
#define COLLECTED_EDGE_WEIGHTED_DIGRAPH_H

#include <string>
#include <vector>

class Edge_weighted_digraph {
    static std::string newline = "\n";

    std::size_t num_vertices;
    std::size_t num_edges;
    // Bag<Directed_edge>[] adj;
    std::vector<std::vector<Directed_edge>> adjacency_list;
    std::vector<int> in_degree;

public:
    Edge_weighted_digraph(std::size_t v) : num_vertices{v}, num_edges{0}, adjacency_list{std::vector<std::vector<Directed_edge>>(v)}, in_degree{std::vector<int>(v)} {
        for (int i = 0; i < num_vertices; i++) {
            adjacency_list[i] = std::vector<std::vector<Directed_edge>>{};
        }
    }

};

#endif //COLLECTED_EDGE_WEIGHTED_DIGRAPH_H
