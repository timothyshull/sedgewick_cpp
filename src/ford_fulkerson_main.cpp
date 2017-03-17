#include "Std_out.h"
#include "Ford_fulkerson.h"
#include "utility.h"

int main(int argc, char* argv[])
{
    int num_vertices{utility::str_to_num(argv[1])};
    int num_edges{utility::str_to_num(argv[2])};
    int s{0};
    int t{num_vertices - 1};

    Flow_network network{num_vertices, num_edges};
    Std_out::print_line(network);

    Ford_fulkerson max_flow{network, s, t};
    Std_out::print_line("Max flow from " + std::to_string(s) + " to " + std::to_string(t));
    for (int v{0}; v < network.num_vertices(); ++v) {
        for (auto e : network.adjacent(v)) {
            if ((v == e.from()) && e.flow() > 0) {
                Std_out::print("   ");
                Std_out::print(e);
                Std_out::print_line();
            }
        }
    }

    Std_out::print("Min cut: ");
    for (int v{0}; v < network.num_vertices(); ++v) {
        if (max_flow.in_cut(v)) { Std_out::print(v + " "); }
    }
    Std_out::print_line();

    Std_out::print_line("Max flow value = " + std::to_string(max_flow.value()));
    return 0;
}