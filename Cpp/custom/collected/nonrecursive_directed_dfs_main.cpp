int main(int argc, char *argv[]) {
    In in = new In(args[0]);
    Digraph G = new Digraph(in);
    int s = Integer.parseInt(args[1]);
    NonrecursiveDirectedDFS dfs = new NonrecursiveDirectedDFS(G, s);
    for (int v = 0; v < G.V(); v++)
        if (dfs.marked(v))
            StdOut.print(v + " ");
    StdOut.println();
    return 0;
}