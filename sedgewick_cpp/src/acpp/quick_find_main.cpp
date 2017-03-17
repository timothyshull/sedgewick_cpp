// Program 1.1 - Quick-find solution to connectivity problem
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    std::size_t num_vertices{std::stoul(argv[1])};
    std::vector<int> id;
    id.reserve(num_vertices);

    int i;
    for (i = 0; i < num_vertices; ++i) { id[i] = i; }

    int t;
    int p;
    int q;
    while (std::cin >> p >> q) {
        t = id[p];
        if (t == id[q]) { continue; }
        for (i = 0; i < num_vertices; ++i) {
            if (id[i] == t) {
                id[i] = id[q];
            }
        }
        std::cout << " " << p << " " << q << "\n";
    }

    return 0;
}