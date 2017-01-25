#include "utility.h"
#include "Digraph.h"
#include "Digraph_generator.h"
#include "Edge_weighted_digraph.h"
#include "Std_out.h"
#include "Topological_x.h"

int main(int argc, char* argv[])
{
    int num_vertices{utility::str_to_num(argv[1])};
    int num_edges{utility::str_to_num(argv[2])};
    int additional_edges{utility::str_to_num(argv[3])};

    Digraph digraph1{Digraph_generator::dag(num_vertices, num_edges)};

    Edge_weighted_digraph digraph2{num_vertices};
    for (int v{0}; v < digraph1.num_vertices(); ++v) {
        for (int w : digraph1.adjacent(v)) {
            digraph2.add_edge(v, w, 0.0);
        }
    }

    for (int i{0}; i < additional_edges; ++i) {
        int v = Std_random::uniform(num_vertices);
        int w = Std_random::uniform(num_vertices);
        digraph1.add_edge(v, w);
        digraph2.add_edge(v, w, 0.0);
    }

    Std_out::print_line(digraph1);
    Std_out::print_line();
    Std_out::print_line(digraph2);

    Topological_x topological1{digraph1};
    if (!topological1.has_order()) {
        Std_out::print_line("Not a DAG");
    } else {
        Std_out::print("Topological order: ");
        for (int v : topological1.order()) {
            Std_out::print(v + " ");
        }
        Std_out::print_line();
    }

    Topological_x topological2{digraph2};
    if (!topological2.has_order()) {
        Std_out::print_line("Not a DAG");
    } else {
        Std_out::print("Topological order: ");
        for (int v : topological2.order()) {
            Std_out::print(v + " ");
        }
        Std_out::print_line();
    }
    return 0;
}