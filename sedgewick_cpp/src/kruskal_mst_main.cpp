#include "Std_out.h"
#include "Edge.h"
#include "Edge_weighted_graph.h"
#include "Kruskal_mst.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    Edge_weighted_graph edge_weighted_graph{in};
    Kruskal_mst mst{edge_weighted_graph};
    for (auto e : mst.edges()) {
        Std_out::print_line(e);
    }
    Std_out::printf("%.5f\n", mst.weight());
    return 0;
}