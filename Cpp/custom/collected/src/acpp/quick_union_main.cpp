// Program 1.2 - Quick-union solution to connectivity problem
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    std::size_t num_vertices{std::stoul(argv[1])};
    std::vector<int> id;
    id.reserve(num_vertices);

    int i;
    for (i = 0; i < num_vertices; ++i) { id[i] = i; }

    int p;
    int q;
    int j;
    while (std::cin >> p >> q) {
        for (i = p; i != id[i]; i = id[i]) {}
        for (j = q; j != id[j]; j = id[j]) {}

        if (i == j) { continue; }
        id[i] = j;
        std::cout << " " << p << " " << q << "\n";
    }
    return 0;
}
