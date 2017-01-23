int main(int argc, char *argv[]) {
    int V = Integer.parseInt(args[0]);
    int E = Integer.parseInt(args[1]);


    // Eulerian cycle
    Graph G1 = GraphGenerator.eulerianCycle(V, E);
    unitTest(G1, "Eulerian cycle");

    // Eulerian path
    Graph G2 = GraphGenerator.eulerianPath(V, E);
    unitTest(G2, "Eulerian path");

    // add one random edge
    Graph G3 = new Graph(G2);
    G3.addEdge(StdRandom.uniform(V), StdRandom.uniform(V));
    unitTest(G3, "one random edge added to Eulerian path");

    // self loop
    Graph G4 = new Graph(V);
    int v4 = StdRandom.uniform(V);
    G4.addEdge(v4, v4);
    unitTest(G4, "single self loop");

    // single edge
    Graph G5 = new Graph(V);
    G5.addEdge(StdRandom.uniform(V), StdRandom.uniform(V));
    unitTest(G5, "single edge");

    // empty graph
    Graph G6 = new Graph(V);
    unitTest(G6, "empty graph");

    // random graph
    Graph G7 = GraphGenerator.simple(V, E);
    unitTest(G7, "simple graph");
    return 0;
}