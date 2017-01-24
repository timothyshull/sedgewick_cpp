int main(int argc, char *argv[]) {
    int V = utility::safe_convert_integer(argv[1]);
    int E = utility::safe_convert_integer(argv[2]);


    // Eulerian cycle
    Graph G1 = Graph_generator::eulerianCycle(V, E);
    unit_test(G1, "Eulerian cycle");

    // Eulerian path
    Graph G2 = Graph_generator::eulerianPath(V, E);
    unit_test(G2, "Eulerian path");

    // add one random edge
    Graph G3 = new Graph(G2);
    G3.add_edge(Std_random::uniform(V), Std_random::uniform(V));
    unit_test(G3, "one random edge added to Eulerian path");

    // self loop
    Graph G4 = new Graph(V);
    int v4 = Std_random::uniform(V);
    G4.add_edge(v4, v4);
    unit_test(G4, "single self loop");

    // single edge
    Graph G5 = new Graph(V);
    G5.add_edge(Std_random::uniform(V), Std_random::uniform(V));
    unit_test(G5, "single edge");

    // empty graph
    Graph G6 = new Graph(V);
    unit_test(G6, "empty graph");

    // random graph
    Graph G7 = Graph_generator::simple(V, E);
    unit_test(G7, "simple graph");
    return 0;
}