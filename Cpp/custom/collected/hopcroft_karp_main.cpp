int main(int argc, char *argv[]) {
    int V1 = utility::safe_convert_integer(argv[1]);
    int V2 = utility::safe_convert_integer(argv[2]);
    int E = utility::safe_convert_integer(argv[3]);
    Graph G = Graph_generator::bipartite(V1, V2, E);
    if (G.num_vertices() < 1000) Std_out::print_line(G);

    HopcroftKarp matching = new HopcroftKarp(G);

    // print maximum matching
    Std_out::printf("Number of edges in max matching        = %d\n", matching.size());
    Std_out::printf("Number of vertices in min vertex cover = %d\n", matching.size());
    Std_out::printf("Graph has a perfect matching           = %b\n", matching.isPerfect());
    Std_out::print_line();

    if (G.num_vertices() >= 1000) return;

    Std_out::print("Max matching: ");
    for (int v = 0; v < G.num_vertices(); ++v) {
        int w = matching.mate(v);
        if (matching.isMatched(v) && v < w)  // print each edge only once
            Std_out::print(v + "-" + w + " ");
    }
    Std_out::print_line();

    // print minimum vertex cover
    Std_out::print("Min vertex cover: ");
    for (int v = 0; v < G.num_vertices(); ++v)
        if (matching.inMinVertexCover(v))
            Std_out::print(v + " ");
    Std_out::print_line();
    return 0;
}