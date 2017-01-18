#include "Adj_matrix_edge_weighted_digraph.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    int num_vertices = atoi(argv[1]);
    int num_edges = atoi(argv[2]);
    Adj_matrix_edge_weighted_digraph g(num_vertices, num_edges);
    Std_out::print_line(g);
    return 0;
}