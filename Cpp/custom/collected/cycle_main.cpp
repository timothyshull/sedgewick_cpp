int main(int argc, char *argv[]) {
    In in = new In(args[0]);
    Graph G = new Graph(in);
    Cycle finder = new Cycle(G);
    if (finder.hasCycle()) {
        for (int v : finder.cycle()) {
            StdOut.print(v + " ");
        }
        StdOut.println();
    } else {
        StdOut.println("Graph is acyclic");
    }
    return 0;
}