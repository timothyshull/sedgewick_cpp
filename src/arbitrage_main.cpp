#include <cmath>
#include "Std_in.h"
#include "Std_out.h"
#include "Edge_weighted_digraph.h"
#include "Bellman_ford_sp.h"

int main() {
    auto num_vertices = static_cast<std::size_t>(Std_in::read_int());
    auto name = std::vector<std::string>(num_vertices);

    auto graph = Edge_weighted_digraph{num_vertices};
    for (auto v = 0; v < num_vertices; ++v) {
        name[v] = Std_in::read_string();
        for (auto w = 0; w < num_vertices; ++w) {
            auto rate = Std_in::read_double();
            Directed_edge e{v, w, -std::log10(rate)};
            graph.add_edge(e);
        }
    }

    auto spt = Bellman_ford_sp{graph, 0};
    if (spt.has_negative_cycle()) {
        auto stake = 1000.0;
        for (auto e : spt.negative_cycle()) {
            Std_out::printf("%10.5f %s ", stake, name[e.from()]);
            stake *= std::exp(-e.weight());
            Std_out::printf("= %10.5f %s\n", stake, name[e.to()]);
        }
    } else {
        Std_out::print_line("No arbitrage opportunity");
    }
    return 0;
}