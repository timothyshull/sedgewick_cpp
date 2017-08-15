#include "utility.h"
#include "Digraph.h"
#include "Std_random.h"
#include "Std_out.h"
#include "Digraph_generator.h"
#include "Directed_cycle_x.h"

int main(int argc, char* argv[])
{
    auto num_vertices = utility::str_to_num(argv[1]);
    auto num_edges = utility::str_to_num(argv[2]);
    auto additional_edges = utility::str_to_num(argv[3]);
    Digraph digraph = Digraph_generator::dag(num_vertices, num_edges);

    int v;
    int w;
    for (auto i = 0; i < additional_edges; ++i) {
        v = Std_random::uniform(num_vertices);
        w = Std_random::uniform(num_vertices);
        digraph.add_edge(v, w);
    }

    Std_out::print_line(digraph);

    Directed_cycle_x finder{digraph};
    if (finder.has_cycle()) {
        Std_out::print("Directed _cycle: ");
        for (auto vx : finder.cycle()) {
            Std_out::print(vx + " ");
        }
        Std_out::print_line();
    } else {
        Std_out::print_line("No directed _cycle");
    }
    Std_out::print_line();
    return 0;
}