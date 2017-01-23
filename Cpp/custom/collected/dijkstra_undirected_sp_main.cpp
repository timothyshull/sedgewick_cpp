int main(int argc, char *argv[]) {
    In in = new In(args[0]);
    EdgeWeightedGraph G = new EdgeWeightedGraph(in);
    int s = Integer.parseInt(args[1]);

    // compute shortest paths
    DijkstraUndirectedSP sp = new DijkstraUndirectedSP(G, s);


    // print shortest path
    for (int t = 0; t < G.V(); t++) {
        if (sp.hasPathTo(t)) {
            StdOut.printf("%d to %d (%.2f)  ", s, t, sp.distTo(t));
            for (Edge e : sp.pathTo(t)) {
                StdOut.print(e + "   ");
            }
            StdOut.println();
        } else {
            StdOut.printf("%d to %d         no path\n", s, t);
        }
    }
    return 0;
}