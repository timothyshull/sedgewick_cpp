#include "Std_out.h"
#include "Graph_generator.h"
#include "utility.h"

int main(int argc, char* argv[])
{
    int num_vertices{utility::str_to_num(argv[1])};
    int num_edges{utility::str_to_num(argv[2])};
    int v1{num_vertices / 2};
    int v2{num_vertices - v1};

    Std_out::print_line("complete graph");
    Std_out::print_line(Graph_generator::complete(num_vertices));
    Std_out::print_line();

    Std_out::print_line("simple");
    Std_out::print_line(Graph_generator::simple(num_vertices, num_edges));
    Std_out::print_line();

    Std_out::print_line("Erdos-Renyi");
    double p = static_cast<double>(num_edges) / (num_vertices * (num_vertices - 1) / 2.0);
    Std_out::print_line(Graph_generator::simple(num_vertices, p));
    Std_out::print_line();

    Std_out::print_line("complete bipartite");
    Std_out::print_line(Graph_generator::complete_bipartite(v1, v2));
    Std_out::print_line();

    Std_out::print_line("bipartite");
    Std_out::print_line(Graph_generator::bipartite(v1, v2, num_edges));
    Std_out::print_line();

    Std_out::print_line("Erdos Renyi bipartite");
    double q = static_cast<double>(num_edges) / (v1 * v2);
    Std_out::print_line(Graph_generator::bipartite(v1, v2, q));
    Std_out::print_line();

    Std_out::print_line("path");
    Std_out::print_line(Graph_generator::path(num_vertices));
    Std_out::print_line();

    Std_out::print_line("cycle");
    Std_out::print_line(Graph_generator::cycle(num_vertices));
    Std_out::print_line();

    Std_out::print_line("binary tree");
    Std_out::print_line(Graph_generator::binary_tree(num_vertices));
    Std_out::print_line();

    Std_out::print_line("tree");
    Std_out::print_line(Graph_generator::tree(num_vertices));
    Std_out::print_line();

    Std_out::print_line("4-regular");
    Std_out::print_line(Graph_generator::regular(num_vertices, 4));
    Std_out::print_line();

    Std_out::print_line("star");
    Std_out::print_line(Graph_generator::star(num_vertices));
    Std_out::print_line();

    Std_out::print_line("wheel");
    Std_out::print_line(Graph_generator::wheel(num_vertices));
    Std_out::print_line();
    return 0;
}