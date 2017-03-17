#include "Adj_matrix_edge_weighted_digraph.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    int num_vertices{utility::str_to_num<int>(argv[1])};
    int num_edges{utility::str_to_num<int>(argv[2])};
    Adj_matrix_edge_weighted_digraph digraph{num_vertices, num_edges};
    Std_out::print_line(digraph);
    return 0;
}
