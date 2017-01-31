#include "In.h"
#include "Edge_weighted_graph.h"
#include "Std_out.h"
#include "Prim_mst.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    Edge_weighted_graph edge_weighted_graph{in};
    Prim_mst mst{edge_weighted_graph};
    for (Edge e : mst.edges()) {
        Std_out::print_line(e);
    }
    Std_out::printf("%.5f\n", mst.weight());
    return 0;
}