int main(int argc, char *argv[]) {
    In in = new In(args[0]);
    Graph G = new Graph(in);
    int s = Integer.parseInt(args[1]);
    DepthFirstPaths dfs = new DepthFirstPaths(G, s);

    for (int v = 0; v < G.V(); v++) {
        if (dfs.hasPathTo(v)) {
            StdOut.printf("%d to %d:  ", s, v);
            for (int x : dfs.pathTo(v)) {
                if (x == s) StdOut.print(x);
                else StdOut.print("-" + x);
            }
            StdOut.println();
        } else {
            StdOut.printf("%d to %d:  not connected\n", s, v);
        }

    }
    return 0;
}