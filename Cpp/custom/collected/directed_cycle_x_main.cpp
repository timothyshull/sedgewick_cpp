#include "utility.h"
#include "Digraph.h"
#include "Std_random.h"
#include "Std_out.h"
#include "Digraph_generator.h"
#include "Directed_cycle_x.h"

int main(int argc, char* argv[])
{
    int num_vertices{utility::safe_convert_integer(argv[1])};
    int num_edges{utility::safe_convert_integer(argv[2])};
    int additional_edges{utility::safe_convert_integer(argv[3])};
    Digraph digraph = Digraph_generator::dag(num_vertices, num_edges);

    int v;
    int w;
    for (int i = 0; i < additional_edges; ++i) {
        v = Std_random::uniform(num_vertices);
        w = Std_random::uniform(num_vertices);
        digraph.add_edge(v, w);
    }

    Std_out::print_line(digraph);

    Directed_cycle_x finder{digraph};
    if (finder.has_cycle()) {
        Std_out::print("Directed cycle: ");
        for (int v : finder.cycle()) {
            Std_out::print(v + " ");
        }
        Std_out::print_line();
    } else {
        Std_out::print_line("No directed cycle");
    }
    Std_out::print_line();
    return 0;
}