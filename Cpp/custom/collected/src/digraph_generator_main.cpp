#include "Std_out.h"
#include "utility.h"
#include "Digraph_generator.h"

int main(int argc, char* argv[])
{
    int num_vertices = utility::str_to_num<int>(argv[1]);
    int num_edges = utility::str_to_num<int>(argv[2]);
    Std_out::print_line("complete graph");
    Std_out::print_line(Digraph_generator::complete(num_vertices));
    Std_out::print_line();

    Std_out::print_line("simple");
    Std_out::print_line(Digraph_generator::simple(num_vertices, num_edges));
    Std_out::print_line();

    Std_out::print_line("path");
    Std_out::print_line(Digraph_generator::path(num_vertices));
    Std_out::print_line();

    Std_out::print_line("cycle");
    Std_out::print_line(Digraph_generator::cycle(num_vertices));
    Std_out::print_line();

    Std_out::print_line("Eulierian path");
    Std_out::print_line(Digraph_generator::eulerian_path(num_vertices, num_edges));
    Std_out::print_line();

    Std_out::print_line("Eulierian _cycle");
    Std_out::print_line(Digraph_generator::eulerian_cycle(num_vertices, num_edges));
    Std_out::print_line();

    Std_out::print_line("binary tree");
    Std_out::print_line(Digraph_generator::binary_tree(num_vertices));
    Std_out::print_line();

    Std_out::print_line("tournament");
    Std_out::print_line(Digraph_generator::tournament(num_vertices));
    Std_out::print_line();

    Std_out::print_line("DAG");
    Std_out::print_line(Digraph_generator::dag(num_vertices, num_edges));
    Std_out::print_line();

    Std_out::print_line("rooted-in DAG");
    Std_out::print_line(Digraph_generator::rooted_in_dag(num_vertices, num_edges));
    Std_out::print_line();

    Std_out::print_line("rooted-out DAG");
    Std_out::print_line(Digraph_generator::rooted_out_dag(num_vertices, num_edges));
    Std_out::print_line();

    Std_out::print_line("rooted-in tree");
    Std_out::print_line(Digraph_generator::rooted_in_tree(num_vertices));
    Std_out::print_line();

    Std_out::print_line("rooted-out tree");
    Std_out::print_line(Digraph_generator::rooted_out_tree(num_vertices));
    Std_out::print_line();
    return 0;
}