#include <cmath>
#include "Std_in.h"
#include "Std_out.h"
#include "Edge_weighted_digraph.h"
#include "Bellman_ford_sp.h"

int main() {
    int num_vertices = Std_in::read_int();
    std::vector<std::string> name{};
    name.reserve(num_vertices);

    Edge_weighted_digraph g{num_vertices};
    double rate;
    for (int v{0}; v < num_vertices; ++v) {
        name[v] = Std_in::read_string();
        for (int w{0}; w < num_vertices; ++w) {
            rate = Std_in::read_double();
            Directed_edge e{v, w, -std::log10(rate)};
            g.add_edge(e);
        }
    }

    Bellman_ford_sp spt{g, 0};
    double stake;
    if (spt.has_negative_cycle()) {
        stake = 1000.0;
        for (auto e : spt.negative_cycle()) {
            Std_out.printf("%10.5f %s ", stake, name[e.from()]);
            stake *= std::exp(-e.weight());
            Std_out.printf("= %10.5f %s\n", stake, name[e.to()]);
        }
    } else {
        Std_out.print_line("No arbitrage opportunity");
    }
    return 0;
}