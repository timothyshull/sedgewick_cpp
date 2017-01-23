int main(int argc, char *argv[]) {
    In in = new In(args[0]);
    Digraph G = new Digraph(in);
    // StdOut.println(G);

    int s = Integer.parseInt(args[1]);
    BreadthFirstDirectedPaths bfs = new BreadthFirstDirectedPaths(G, s);

    for (int v = 0; v < G.V(); v++) {
        if (bfs.hasPathTo(v)) {
            StdOut.printf("%d to %d (%d):  ", s, v, bfs.distTo(v));
            for (int x : bfs.pathTo(v)) {
                if (x == s) StdOut.print(x);
                else StdOut.print("->" + x);
            }
            StdOut.println();
        } else {
            StdOut.printf("%d to %d (-):  not connected\n", s, v);
        }

    }
    return 0;
}
