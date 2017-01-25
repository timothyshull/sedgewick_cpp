#include "utility.h"

int main(int argc, char *argv[]) {
    int num_vertices = utility::str_to_num(argv[1]);
    int E = utility::str_to_num(argv[2]);
    int F = utility::str_to_num(argv[3]);

    Digraph G1 = Digraph_generator::dag(V, E);

    // corresponding edge-weighted digraph
    Edge_weighted_digraph G2 = new Edge_weighted_digraph(V);
    for (int v = 0; v < G1.num_vertices(); ++v)
        for (int w : G1.adj(v))
            G2.add_edge(new Directed_edge(v, w, 0.0));

    // add F extra edges
    for (int i = 0; i < F; ++i) {
        int v = Std_random::uniform(V);
        int w = Std_random::uniform(V);
        G1.add_edge(v, w);
        G2.add_edge(new Directed_edge(v, w, 0.0));
    }

    Std_out::print_line(G1);
    Std_out::print_line();
    Std_out::print_line(G2);

    // find a directed cycle
    TopologicalX topological1 = new TopologicalX(G1);
    if (!topological1.hasOrder()) {
        Std_out::print_line("Not a DAG");
    }

        // or give topologial sort
    else {
        Std_out::print("Topological order: ");
        for (int v : topological1.order()) {
            Std_out::print(v + " ");
        }
        Std_out::print_line();
    }

    // find a directed cycle
    TopologicalX topological2 = new TopologicalX(G2);
    if (!topological2.hasOrder()) {
        Std_out::print_line("Not a DAG");
    }

        // or give topologial sort
    else {
        Std_out::print("Topological order: ");
        for (int v : topological2.order()) {
            Std_out::print(v + " ");
        }
        Std_out::print_line();
    }
    return 0;
}