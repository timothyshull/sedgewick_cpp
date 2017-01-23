int main(int argc, char *argv[]) {
    int V = Integer.parseInt(args[0]);
    int E = Integer.parseInt(args[1]);

    // Eulerian cycle
    Digraph G1 = DigraphGenerator.eulerianCycle(V, E);
    unitTest(G1, "Eulerian cycle");

    // Eulerian path
    Digraph G2 = DigraphGenerator.eulerianPath(V, E);
    unitTest(G2, "Eulerian path");

    // empty digraph
    Digraph G3 = new Digraph(V);
    unitTest(G3, "empty digraph");

    // self loop
    Digraph G4 = new Digraph(V);
    int v4 = StdRandom.uniform(V);
    G4.addEdge(v4, v4);
    unitTest(G4, "single self loop");

    // union of two disjoint cycles
    Digraph H1 = DigraphGenerator.eulerianCycle(V / 2, E / 2);
    Digraph H2 = DigraphGenerator.eulerianCycle(V - V / 2, E - E / 2);
    int[] perm = new int[V];
    for (int i = 0; i < V; i++)
        perm[i] = i;
    StdRandom.shuffle(perm);
    Digraph G5 = new Digraph(V);
    for (int v = 0; v < H1.V(); v++)
        for (int w : H1.adj(v))
            G5.addEdge(perm[v], perm[w]);
    for (int v = 0; v < H2.V(); v++)
        for (int w : H2.adj(v))
            G5.addEdge(perm[V / 2 + v], perm[V / 2 + w]);
    unitTest(G5, "Union of two disjoint cycles");

    // random digraph
    Digraph G6 = DigraphGenerator.simple(V, E);
    unitTest(G6, "simple digraph");

    // 4-vertex digraph
    Digraph G7 = new Digraph(new In("eulerianD.txt"));
    unitTest(G7, "4-vertex Eulerian digraph");
    return 0;
}