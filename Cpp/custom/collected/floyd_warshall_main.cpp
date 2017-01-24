int main(int argc, char *argv[]) {
    int V = utility::safe_convert_integer(argv[1]);
    int E = utility::safe_convert_integer(argv[2]);
    Adj_matrix_edge_weighted_digraph G = new Adj_matrix_edge_weighted_digraph(V);
    for (int i = 0; i < E; ++i) {
        int v = Std_random::uniform(V);
        int w = Std_random::uniform(V);
        double weight = Math.round(100 * (Std_random::uniform() - 0.15)) / 100.0;
        if (v == w) G.add_edge(new Directed_edge(v, w, Math.abs(weight)));
        else G.add_edge(new Directed_edge(v, w, weight));
    }

    Std_out::print_line(G);

    // run Floyd-Warshall algorithm
    FloydWarshall spt = new FloydWarshall(G);

    // print all-pairs shortest path distances
    Std_out::printf("  ");
    for (int v = 0; v < G.num_vertices(); ++v) {
        Std_out::printf("%6d ", v);
    }
    Std_out::print_line();
    for (int v = 0; v < G.num_vertices(); ++v) {
        Std_out::printf("%3d: ", v);
        for (int w = 0; w < G.num_vertices(); ++w) {
            if (spt.hasPath(v, w)) Std_out::printf("%6.2f ", spt.dist(v, w));
            else Std_out::printf("  Inf ");
        }
        Std_out::print_line();
    }

    // print negative cycle
    if (spt.hasNegativeCycle()) {
        Std_out::print_line("Negative cost cycle:");
        for (Directed_edge e : spt.negativeCycle())
            Std_out::print_line(e);
        Std_out::print_line();
    }

        // print all-pairs shortest paths
    else {
        for (int v = 0; v < G.num_vertices(); ++v) {
            for (int w = 0; w < G.num_vertices(); ++w) {
                if (spt.hasPath(v, w)) {
                    Std_out::printf("%d to %d (%5.2f)  ", v, w, spt.dist(v, w));
                    for (Directed_edge e : spt.path(v, w))
                        Std_out::print(e + "  ");
                    Std_out::print_line();
                } else {
                    Std_out::printf("%d to %d no path\n", v, w);
                }
            }
        }
    }
    return 0;
}