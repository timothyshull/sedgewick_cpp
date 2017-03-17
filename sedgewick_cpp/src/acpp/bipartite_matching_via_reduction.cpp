// Program 22.7 - Bipartite matching via reduction to maxflow
#include <string>
#include <iostream>

#include "Edge.h"
#include "Sparse_multigraph.h"
#include "Maxflow_augmenting_paths.h"
#include "Flow_network_edge.h"

int main(int argc, char* argv[])
{
    int s;
    int t;
    int num_vertices{std::stoi(argv[1])};
    Sparse_multigraph<Edge> graph(2 * num_vertices + 2);
    for (int i{0}; i < num_vertices; ++i) {
        graph.insert(new Flow_network_edge{2 * num_vertices, i, 1});
    }
    while (std::cin >> s >> t) {
        graph.insert(new Flow_network_edge{s, t, 1});
    }
    for (int i{num_vertices}; i < 2 * num_vertices; ++i) {
        graph.insert(new Flow_network_edge{i, 2 * num_vertices + 1, 1});
    }
    Maxflow_augmenting_paths<Sparse_multigraph<Edge>, Edge>{graph, 2 * num_vertices, 2 * num_vertices + 1};
    for (int i{0}; i < num_vertices; ++i) {
        // Sparse_multigraph<Edge>::adjIterator A(graph, i);
        for (auto e : graph.adjacent(i)) {
            if (e->flow() == 1 && e->from(i)) {
                std::cout << e->source() << "-" << e->destination() << "\n";
            }
        }
    }

    return 0;
}

