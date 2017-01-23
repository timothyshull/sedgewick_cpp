int main(int argc, char *argv[]) {
    int V = Integer.parseInt(args[0]);
    int E = Integer.parseInt(args[1]);
    AdjMatrixEdgeWeightedDigraph G = new AdjMatrixEdgeWeightedDigraph(V);
    for (int i = 0; i < E; i++) {
        int v = StdRandom.uniform(V);
        int w = StdRandom.uniform(V);
        double weight = Math.round(100 * (StdRandom.uniform() - 0.15)) / 100.0;
        if (v == w) G.addEdge(new DirectedEdge(v, w, Math.abs(weight)));
        else G.addEdge(new DirectedEdge(v, w, weight));
    }

    StdOut.println(G);

    // run Floyd-Warshall algorithm
    FloydWarshall spt = new FloydWarshall(G);

    // print all-pairs shortest path distances
    StdOut.printf("  ");
    for (int v = 0; v < G.V(); v++) {
        StdOut.printf("%6d ", v);
    }
    StdOut.println();
    for (int v = 0; v < G.V(); v++) {
        StdOut.printf("%3d: ", v);
        for (int w = 0; w < G.V(); w++) {
            if (spt.hasPath(v, w)) StdOut.printf("%6.2f ", spt.dist(v, w));
            else StdOut.printf("  Inf ");
        }
        StdOut.println();
    }

    // print negative cycle
    if (spt.hasNegativeCycle()) {
        StdOut.println("Negative cost cycle:");
        for (DirectedEdge e : spt.negativeCycle())
            StdOut.println(e);
        StdOut.println();
    }

        // print all-pairs shortest paths
    else {
        for (int v = 0; v < G.V(); v++) {
            for (int w = 0; w < G.V(); w++) {
                if (spt.hasPath(v, w)) {
                    StdOut.printf("%d to %d (%5.2f)  ", v, w, spt.dist(v, w));
                    for (DirectedEdge e : spt.path(v, w))
                        StdOut.print(e + "  ");
                    StdOut.println();
                } else {
                    StdOut.printf("%d to %d no path\n", v, w);
                }
            }
        }
    }
    return 0;
}