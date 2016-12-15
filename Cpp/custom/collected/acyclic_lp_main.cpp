#include<iostream>
#include<string>
#include<fstream>

#include"Acyclic_LP.h"

int main(int argc, char *argv[]) {
    std::fstream f{argv[1]};
    std::size_t s{static_cast<std::size_t>(std::atoi(argv[2]))};
    Edge_weighted_digraph g{f};

    Acyclic_LP lp{g, s};

    for (int v = 0; v < g.num_vertices(); v++) {
        if (lp.has_path_to(v)) {
            std::cout << s << " to " << v << "" << lp.get_distance_to(v) << "\n";

            for (auto e : lp.path_to(v)) {
                std::cout << e << "    ";
            }
            std::cout << "\n";
        } else {
            std::cout << s << " to " << v << ": no path\n";
        }
    }

    return 0;
}
