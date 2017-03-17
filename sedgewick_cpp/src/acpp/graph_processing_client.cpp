#include <iostream>
#include <cstdlib>
#include "Graph.h"
#include "Graph_io.h"
#include "Basic_connectivity.h"

int main(int argc, char* argv[])
{
    std::size_t num_vertices{std::stoul(argv[1])};
    Graph graph{num_vertices};
    Graph_io<Graph>::scan(graph);
    if (num_vertices < 20) { Graph_io<Graph>::show(graph); }
    std::cout << graph.num_edges() << " edges ";
    Connected_component<Graph> connected_component{graph};
    std::cout << connected_component.count() << " components" << "\n";
    return 0;
}