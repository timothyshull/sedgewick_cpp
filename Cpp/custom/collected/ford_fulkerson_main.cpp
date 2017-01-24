int main(int argc, char *argv[]) {
    int V = utility::safe_convert_integer(argv[1]);
    int E = utility::safe_convert_integer(argv[2]);
    int s = 0, t = V - 1;
    FlowNetwork G = new FlowNetwork(V, E);
    Std_out::print_line(G);

    // compute maximum flow and minimum cut
    FordFulkerson maxflow = new FordFulkerson(G, s, t);
    Std_out::print_line("Max flow from " + s + " to " + t);
    for (int v = 0; v < G.num_vertices(); ++v) {
        for (FlowEdge e : G.adj(v)) {
            if ((v == e.from()) && e.flow() > 0)
                Std_out::print_line("   " + e);
        }
    }

    // print min-cut
    Std_out::print("Min cut: ");
    for (int v = 0; v < G.num_vertices(); ++v) {
        if (maxflow.inCut(v)) Std_out::print(v + " ");
    }
    Std_out::print_line();

    Std_out::print_line("Max flow value = " + maxflow.value());
    return 0;
}