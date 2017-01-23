int main(int argc, char *argv[]) {
    In in = new In(args[0]);
    Graph G = new Graph(in);
    int s = Integer.parseInt(args[1]);
    DepthFirstSearch search = new DepthFirstSearch(G, s);
    for (int v = 0; v < G.V(); v++) {
        if (search.marked(v))
            StdOut.print(v + " ");
    }

    StdOut.println();
    if (search.count() != G.V()) StdOut.println("NOT connected");
    else StdOut.println("connected");
    return 0;
}