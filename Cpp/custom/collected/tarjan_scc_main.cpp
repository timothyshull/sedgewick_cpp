int main(int argc, char *argv[]) {
    In in = new In(args[0]);
    Digraph G = new Digraph(in);
    TarjanSCC scc = new TarjanSCC(G);

    // number of connected components
    int m = scc.count();
    StdOut.println(m + " components");

    // compute list of vertices in each strong component
    Queue<Integer>[] components = (Queue<Integer>[]) new Queue[m];
    for (int i = 0; i < m; i++) {
        components[i] = new Queue<Integer>();
    }
    for (int v = 0; v < G.V(); v++) {
        components[scc.id(v)].enqueue(v);
    }

    // print results
    for (int i = 0; i < m; i++) {
        for (int v : components[i]) {
            StdOut.print(v + " ");
        }
        StdOut.println();
    }
    return 0;
}
