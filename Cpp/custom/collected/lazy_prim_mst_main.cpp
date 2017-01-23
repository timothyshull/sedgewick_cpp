int main(int argc, char *argv[]) {
    In in = new In(args[0]);
    EdgeWeightedGraph G = new EdgeWeightedGraph(in);
    LazyPrimMST mst = new LazyPrimMST(G);
    for (Edge e : mst.edges()) {
        StdOut.println(e);
    }
    StdOut.printf("%.5f\n", mst.weight());
    return 0;
}