int main(int argc, char *argv[]) {
    int V1 = Integer.parseInt(args[0]);
    int V2 = Integer.parseInt(args[1]);
    int E = Integer.parseInt(args[2]);
    Graph G = GraphGenerator.bipartite(V1, V2, E);
    if (G.V() < 1000) StdOut.println(G);

    HopcroftKarp matching = new HopcroftKarp(G);

    // print maximum matching
    StdOut.printf("Number of edges in max matching        = %d\n", matching.size());
    StdOut.printf("Number of vertices in min vertex cover = %d\n", matching.size());
    StdOut.printf("Graph has a perfect matching           = %b\n", matching.isPerfect());
    StdOut.println();

    if (G.V() >= 1000) return;

    StdOut.print("Max matching: ");
    for (int v = 0; v < G.V(); v++) {
        int w = matching.mate(v);
        if (matching.isMatched(v) && v < w)  // print each edge only once
            StdOut.print(v + "-" + w + " ");
    }
    StdOut.println();

    // print minimum vertex cover
    StdOut.print("Min vertex cover: ");
    for (int v = 0; v < G.V(); v++)
        if (matching.inMinVertexCover(v))
            StdOut.print(v + " ");
    StdOut.println();
    return 0;
}