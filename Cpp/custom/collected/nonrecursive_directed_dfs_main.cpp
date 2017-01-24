int main(int argc, char *argv[]) {
    In in{argv[1]};
    Digraph G{in};
    int s = utility::safe_convert_integer(argv[1]);
    NonrecursiveDirectedDFS dfs = new NonrecursiveDirectedDFS(G, s);
    for (int v = 0; v < G.num_vertices(); ++v)
        if (dfs.marked(v))
            Std_out::print(v + " ");
    Std_out::print_line();
    return 0;
}