int main(int argc, char *argv[]) {
    In in = new In(args[0]);
    Digraph G = new Digraph(in);

    // read in sources from command-line arguments
    Bag<Integer> sources = new Bag<Integer>();
    for (int i = 1; i < args.length; i++) {
        int s = Integer.parseInt(args[i]);
        sources.add(s);
    }

    // multiple-source reachability
    DirectedDFS dfs = new DirectedDFS(G, sources);

    // print out vertices reachable from sources
    for (int v = 0; v < G.V(); v++) {
        if (dfs.marked(v)) StdOut.print(v + " ");
    }
    StdOut.println();
    return 0;
}