int main(int argc, char *argv[]) {
    int V = Integer.parseInt(args[0]);
    int E = Integer.parseInt(args[1]);
    int F = Integer.parseInt(args[2]);

    Digraph G1 = DigraphGenerator.dag(V, E);

    // corresponding edge-weighted digraph
    EdgeWeightedDigraph G2 = new EdgeWeightedDigraph(V);
    for (int v = 0; v < G1.V(); v++)
        for (int w : G1.adj(v))
            G2.addEdge(new DirectedEdge(v, w, 0.0));

    // add F extra edges
    for (int i = 0; i < F; i++) {
        int v = StdRandom.uniform(V);
        int w = StdRandom.uniform(V);
        G1.addEdge(v, w);
        G2.addEdge(new DirectedEdge(v, w, 0.0));
    }

    StdOut.println(G1);
    StdOut.println();
    StdOut.println(G2);

    // find a directed cycle
    TopologicalX topological1 = new TopologicalX(G1);
    if (!topological1.hasOrder()) {
        StdOut.println("Not a DAG");
    }

        // or give topologial sort
    else {
        StdOut.print("Topological order: ");
        for (int v : topological1.order()) {
            StdOut.print(v + " ");
        }
        StdOut.println();
    }

    // find a directed cycle
    TopologicalX topological2 = new TopologicalX(G2);
    if (!topological2.hasOrder()) {
        StdOut.println("Not a DAG");
    }

        // or give topologial sort
    else {
        StdOut.print("Topological order: ");
        for (int v : topological2.order()) {
            StdOut.print(v + " ");
        }
        StdOut.println();
    }
    return 0;
}