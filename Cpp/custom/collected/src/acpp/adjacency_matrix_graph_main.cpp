// Program 3.18 - Adjacency matrix graph representation
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    std::size_t num_vertices{std::stoul(argv[1])};
    std::vector<std::vector<int>> adj;
    adj.reserve(num_vertices);

    int i;
    int j;
    for (i = 0; i < num_vertices; ++i) {
        adj[i].reserve(num_vertices);
        // for (j = 0; j < num_vertices; ++j) {
        //     adj[i][j] = 0;
        // }
    }

    for (i = 0; i < num_vertices; ++i) { adj[i][i] = 1; }
    while (std::cin >> i >> j) {
        adj[i][j] = 1;
        adj[j][i] = 1;
    }
    return 0;
}