#include <iostream>
#include <fstream>

#include "Acyclic_lp.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::ifstream in(argv[1]);
    int s = utility::safe_convert_integer(argv[2]);
    // Edge_weighted_digraph g{in};
    Edge_weighted_digraph g{std::cin};

    Acyclic_lp lp{g, s};

    for (int v = 0; v < g.num_vertices(); ++v) {
        if (lp.has_path_to(v)) {
            Std_out::printf("%d to %d (%.2f)  ", s, v, lp.distance_to(v));
            for (Directed_edge e : lp.path_to(v)) {
                Std_out::print(e);
                Std_out::print("    ");
            }
            Std_out::print_line();
        } else {
            Std_out::printf("%d to %d         no path\n", s, v);
        }
    }

    return 0;
}
