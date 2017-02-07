// Program 1.4 - Path compression by halving
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    std::size_t num_vertices{std::stoul(argv[1])};
    std::vector<int> id;
    id.reserve(num_vertices);

    std::vector<int> sz;
    sz.reserve(num_vertices);

    int i;
    for (i = 0; i < num_vertices; ++i) {
        id[i] = i;
        sz[i] = 1;
    }

    int p;
    int q;
    int j;
    while (std::cin >> p >> q) {
        for (i = p; i != id[i]; i = id[i]) {
            id[i] = id[id[i]];
        }
        for (j = q; j != id[j]; j = id[j]) {
            id[j] = id[id[j]];
        }
        if (i == j) { continue; }
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
        } else {
            id[j] = i;
            sz[i] += sz[j];
        }
        std::cout << " " << p << " " << q << "\n";
    }
    return 0;
}
