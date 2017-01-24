#include "In.h"
#include "Edge_weighted_graph.h"
#include "Std_out.h"
#include "Boruvka_mst.h"

int main(int argc, char* argv[])
{
    In in{argv[1]};
    Edge_weighted_graph g{in};
    Boruvka_mst mst{g};
    for (auto e : mst.edges()) {
        Std_out::print_line(e);
    }
    Std_out::printf("%.5f\n", mst.weight());
    return 0;
}