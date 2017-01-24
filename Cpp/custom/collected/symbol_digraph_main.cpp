int main(int argc, char *argv[]) {
    String filename = args[0];
    String delimiter = args[1];
    SymbolDigraph sg = new SymbolDigraph(filename, delimiter);
    Digraph graph = sg.digraph();
    while (!StdIn.isEmpty()) {
        String t = StdIn.readLine();
        for (int v : graph.adj(sg.index(t))) {
            StdOut.println("   " + sg.name(v));
        }
    }
    return 0;
}