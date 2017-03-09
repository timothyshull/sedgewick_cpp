#include "In.h"
#include "Acyclic_sp.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    auto s = utility::str_to_num<int>(argv[2]);
    Edge_weighted_digraph digraph{in};

    Acyclic_sp sp{digraph, s};
    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        if (sp.has_path_to(v)) {
            Std_out::printf("%d to %d (%.2f)  ", s, v, sp.distance_to(v));
            for (auto& e : sp.path_to(v)) {
                Std_out::print(e.to_string() + "   ");
            }
            Std_out::print_line();
        } else {
            Std_out::printf("%d to %d         no path\n", s, v);
        }
    }
}