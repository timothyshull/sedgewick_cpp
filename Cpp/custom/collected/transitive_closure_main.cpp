int main(int argc, char *argv[]) {
    In in = new In(args[0]);
    Digraph G = new Digraph(in);

    TransitiveClosure tc = new TransitiveClosure(G);

    // print header
    StdOut.print("     ");
    for (int v = 0; v < G.V(); v++)
        StdOut.printf("%3d", v);
    StdOut.println();
    StdOut.println("--------------------------------------------");

    // print transitive closure
    for (int v = 0; v < G.V(); v++) {
        StdOut.printf("%3d: ", v);
        for (int w = 0; w < G.V(); w++) {
            if (tc.reachable(v, w)) StdOut.printf("  T");
            else StdOut.printf("   ");
        }
        StdOut.println();
    }
    return 0;
}