int main(int argc, char *argv[]) {
    int V = Integer.parseInt(args[0]);
    int E = Integer.parseInt(args[1]);


    // Eulerian cycle
    Digraph G1 = DigraphGenerator.eulerianCycle(V, E);
    unitTest(G1, "Eulerian cycle");

    // Eulerian path
    Digraph G2 = DigraphGenerator.eulerianPath(V, E);
    unitTest(G2, "Eulerian path");

    // add one random edge
    Digraph G3 = new Digraph(G2);
    G3.addEdge(StdRandom.uniform(V), StdRandom.uniform(V));
    unitTest(G3, "one random edge added to Eulerian path");

    // self loop
    Digraph G4 = new Digraph(V);
    int v4 = StdRandom.uniform(V);
    G4.addEdge(v4, v4);
    unitTest(G4, "single self loop");

    // single edge
    Digraph G5 = new Digraph(V);
    G5.addEdge(StdRandom.uniform(V), StdRandom.uniform(V));
    unitTest(G5, "single edge");

    // empty digraph
    Digraph G6 = new Digraph(V);
    unitTest(G6, "empty digraph");

    // random digraph
    Digraph G7 = DigraphGenerator.simple(V, E);
    unitTest(G7, "simple digraph");

    // 4-vertex digraph
    Digraph G8 = new Digraph(new In("eulerianD.txt"));
    unitTest(G8, "4-vertex Eulerian digraph");
    return 0;
}