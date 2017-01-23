int main(int argc, char *argv[]) {
    int V = Integer.parseInt(args[0]);
    int E = Integer.parseInt(args[1]);

    // Eulerian cycle
    Graph G1 = GraphGenerator.eulerianCycle(V, E);
    unitTest(G1, "Eulerian cycle");

    // Eulerian path
    Graph G2 = GraphGenerator.eulerianPath(V, E);
    unitTest(G2, "Eulerian path");

    // empty graph
    Graph G3 = new Graph(V);
    unitTest(G3, "empty graph");

    // self loop
    Graph G4 = new Graph(V);
    int v4 = StdRandom.uniform(V);
    G4.addEdge(v4, v4);
    unitTest(G4, "single self loop");

    // union of two disjoint cycles
    Graph H1 = GraphGenerator.eulerianCycle(V / 2, E / 2);
    Graph H2 = GraphGenerator.eulerianCycle(V - V / 2, E - E / 2);
    int[] perm = new int[V];
    for (int i = 0; i < V; i++)
        perm[i] = i;
    StdRandom.shuffle(perm);
    Graph G5 = new Graph(V);
    for (int v = 0; v < H1.V(); v++)
        for (int w : H1.adj(v))
            G5.addEdge(perm[v], perm[w]);
    for (int v = 0; v < H2.V(); v++)
        for (int w : H2.adj(v))
            G5.addEdge(perm[V / 2 + v], perm[V / 2 + w]);
    unitTest(G5, "Union of two disjoint cycles");

    // random digraph
    Graph G6 = GraphGenerator.simple(V, E);
    unitTest(G6, "simple graph");
    return 0;
}