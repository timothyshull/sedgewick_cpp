int main(int argc, char *argv[]) {
    In in{argv[1]};
    Digraph G{in};
    GabowSCC scc = new GabowSCC(G);

    // number of connected components
    int m = scc.count();
    Std_out::print_line(m + " components");

    // compute list of vertices in each strong component
    Queue<Integer>[] components = (Queue<Integer>[]) new Queue[m];
    for (int i = 0; i < m; ++i) {
        components[i] = new Queue<Integer>();
    }
    for (int v = 0; v < G.num_vertices(); ++v) {
        components[scc.id(v)].enqueue(v);
    }

    // print results
    for (int i = 0; i < m; ++i) {
        for (int v : components[i]) {
            Std_out::print(v + " ");
        }
        Std_out::print_line();
    }
    return 0;
}