int main(int argc, char *argv[]) {
    In in = new In(args[0]);
    Graph G = new Graph(in);
    CC cc = new CC(G);

    // number of connected components
    int m = cc.count();
    StdOut.println(m + " components");

    // compute list of vertices in each connected component
    Queue<Integer>[] components = (Queue<Integer>[]) new Queue[m];
    for (int i = 0; i < m; i++) {
        components[i] = new Queue<Integer>();
    }
    for (int v = 0; v < G.V(); v++) {
        components[cc.id(v)].enqueue(v);
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