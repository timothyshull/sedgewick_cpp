#include "In.h"
#include "Bellman_ford_sp.h"
#include "Std_out.h"

int main(int argc, char *argv[]) {
    In<std::ifstream> in{argv[1]};
    auto s = utility::str_to_num<int>(argv[2]);
    Edge_weighted_digraph g{in};

    Bellman_ford_sp sp{g, s};

    if (sp.has_negative_cycle()) {
        for (Directed_edge e : sp.negative_cycle())
            Std_out::print_line(e);
    } else {
        for (auto v = 0; v < g.num_vertices(); ++v) {
            if (sp.has_path_to(v)) {
                Std_out::printf("%d to %d (%5.2f)  ", s, v, sp.distance_to(v));
                for (Directed_edge e : sp.path_to(v)) {
                    Std_out::print(e.to_string() + "   ");
                }
                Std_out::print_line();
            } else {
                Std_out::printf("%d to %d           no path\n", s, v);
            }
        }
    }
    return 0;
}