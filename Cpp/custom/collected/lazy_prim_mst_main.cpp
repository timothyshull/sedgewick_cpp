#include "In.h"
#include "Edge_weighted_graph.h"
#include "Lazy_prim_mst.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    In in{argv[1]};
    Edge_weighted_graph edge_weighted_graph{in};
    Lazy_prim_mst mst{edge_weighted_graph};
    for (auto e : mst.edges()) {
        Std_out::print_line(e);
    }
    Std_out::printf("%.5f\n", mst.weight());
    return 0;
}