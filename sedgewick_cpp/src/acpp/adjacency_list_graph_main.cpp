// Program 3.19 - Adjacency lists graph representation
#include <iostream>
#include <vector>

#include "free_list.h"

int main(int argc, char* argv[])
{
    std::size_t num_vertices{std::stoul(argv[1])};
    std::vector<Raw_node_pointer> adj{num_vertices, nullptr};

    int i;
    int j;
    while (std::cin >> i >> j) {
        adj[j] = new Node{i, adj[j]};
        adj[i] = new Node{j, adj[i]};
    }
    return 0;
}
