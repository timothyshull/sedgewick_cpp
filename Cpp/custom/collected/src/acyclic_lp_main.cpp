#include "Acyclic_lp.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    int s{utility::str_to_num<int>(argv[2])};
    Edge_weighted_digraph digraph{in};

    Acyclic_lp lp{digraph, s};

    for (int v{0}; v < digraph.num_vertices(); ++v) {
        if (lp.has_path_to(v)) {
            Std_out::printf("%d to %d (%.2f)  ", s, v, lp.distance_to(v));
            for (auto e : lp.path_to(v)) {
                Std_out::print(e.to_string() + "   ");
            }
            Std_out::print_line();
        } else {
            Std_out::printf("%d to %d         no path\n", s, v);
        }
    }

    return 0;
}
