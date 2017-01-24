int main(int argc, char *argv[]) {
    int V = utility::safe_convert_integer(argv[1]);
    int E = utility::safe_convert_integer(argv[2]);

    // Eulerian cycle
    Graph G1 = Graph_generator::eulerianCycle(V, E);
    unit_test(G1, "Eulerian cycle");

    // Eulerian path
    Graph G2 = Graph_generator::eulerianPath(V, E);
    unit_test(G2, "Eulerian path");

    // empty graph
    Graph G3 = new Graph(V);
    unit_test(G3, "empty graph");

    // self loop
    Graph G4 = new Graph(V);
    int v4 = Std_random::uniform(V);
    G4.add_edge(v4, v4);
    unit_test(G4, "single self loop");

    // union of two disjoint cycles
    Graph H1 = Graph_generator::eulerianCycle(V / 2, E / 2);
    Graph H2 = Graph_generator::eulerianCycle(V - V / 2, E - E / 2);
    std::vector<int> perm = new int[V];
    for (int i = 0; i < V; ++i)
        perm[i] = i;
    Std_random::shuffle(perm);
    Graph G5 = new Graph(V);
    for (int v = 0; v < H1.num_vertices(); ++v)
        for (int w : H1.adj(v))
            G5.add_edge(perm[v], perm[w]);
    for (int v = 0; v < H2.num_vertices(); ++v)
        for (int w : H2.adj(v))
            G5.add_edge(perm[V / 2 + v], perm[V / 2 + w]);
    unit_test(G5, "Union of two disjoint cycles");

    // random digraph
    Graph G6 = Graph_generator::simple(V, E);
    unit_test(G6, "simple graph");
    return 0;
}