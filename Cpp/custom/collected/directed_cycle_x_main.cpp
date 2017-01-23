int main(int argc, char *argv[]) {
    int V = Integer.parseInt(args[0]);
    int E = Integer.parseInt(args[1]);
    int F = Integer.parseInt(args[2]);
    Digraph G = DigraphGenerator.dag(V, E);

    // add F extra edges
    for (int i = 0; i < F; i++) {
        int v = StdRandom.uniform(V);
        int w = StdRandom.uniform(V);
        G.addEdge(v, w);
    }

    StdOut.println(G);


    DirectedCycleX finder = new DirectedCycleX(G);
    if (finder.hasCycle()) {
        StdOut.print("Directed cycle: ");
        for (int v : finder.cycle()) {
            StdOut.print(v + " ");
        }
        StdOut.println();
    } else {
        StdOut.println("No directed cycle");
    }
    StdOut.println();
    return 0;
}