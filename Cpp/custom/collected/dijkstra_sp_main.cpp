int main(int argc, char *argv[]) {
    In in = new In(args[0]);
    EdgeWeightedDigraph G = new EdgeWeightedDigraph(in);
    int s = Integer.parseInt(args[1]);

    // compute shortest paths
    DijkstraSP sp = new DijkstraSP(G, s);


    // print shortest path
    for (int t = 0; t < G.V(); t++) {
        if (sp.hasPathTo(t)) {
            StdOut.printf("%d to %d (%.2f)  ", s, t, sp.distTo(t));
            for (DirectedEdge e : sp.pathTo(t)) {
                StdOut.print(e + "   ");
            }
            StdOut.println();
        } else {
            StdOut.printf("%d to %d         no path\n", s, t);
        }
    }
    return 0;
}