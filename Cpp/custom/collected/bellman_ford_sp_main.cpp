

int main(int argc, char *argv[]) {
    In in = new In(args[0]);
    int s = Integer.parseInt(args[1]);
    EdgeWeightedDigraph G = new EdgeWeightedDigraph(in);

    BellmanFordSP sp = new BellmanFordSP(G, s);

    // print negative cycle
    if (sp.hasNegativeCycle()) {
        for (DirectedEdge e : sp.negativeCycle())
            StdOut.println(e);
    }

        // print shortest paths
    else {
        for (int v = 0; v < G.V(); v++) {
            if (sp.hasPathTo(v)) {
                StdOut.printf("%d to %d (%5.2f)  ", s, v, sp.distTo(v));
                for (DirectedEdge e : sp.pathTo(v)) {
                    StdOut.print(e + "   ");
                }
                StdOut.println();
            } else {
                StdOut.printf("%d to %d           no path\n", s, v);
            }
        }
    }
    return 0;
}