#include "Dense_graph.h"
#include "Graph_io.h"
#include "Longest_paths_dag.h"


// typedef WeightedEdge EDGE;

// typedef DenseGRAPH <EDGE> GRAPH;

int main(int argc, char* argv[])
{
    int i;
    int s;
    int t;
    auto num_vertices = std::stoi(argv[1]);
    std::vector<double> duration;
    duration.reserve(static_cast<std::vector<double>::size_type>(num_vertices));
    Dense_graph graph{num_vertices, true};
    for (auto i = 0; i < num_vertices; ++i) {
        std::cin >> duration[i];
    }
    while (std::cin >> s >> t) {
        graph.insert(new Edge{s, t, duration[s]});
    }
    Longest_paths_dag <Dense_graph, Edge> lpt{graph};
    for (i = 0; i < num_vertices; ++i) {
        std::cout << i << " " << lpt.distance(i) << "\n";
    }

    return 0;
}

