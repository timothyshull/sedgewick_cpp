int main(int argc, char* argv[])
{
    In in{argv[1]};
    Graph G = new Graph(in);
    int s = utility::safe_convert_integer(argv[1]);
    NonrecursiveDFS dfs = new NonrecursiveDFS(G, s);
    for (int v = 0; v < G.num_vertices(); ++v) {
        if (dfs.marked(v)) {
            Std_out::print(v + " ");
        }
    }
    Std_out::print_line();
    return 0;
}