int main(int argc, char *argv[]) {
    String filename = args[0];
    String delimiter = args[1];
    SymbolGraph sg = new SymbolGraph(filename, delimiter);
    Graph graph = sg.graph();
    while (StdIn.hasNextLine()) {
        String source = StdIn.readLine();
        if (sg.contains(source)) {
            int s = sg.index(source);
            for (int v : graph.adj(s)) {
                StdOut.println("   " + sg.name(v));
            }
        } else {
            StdOut.println("input not contain '" + source + "'");
        }
    }
    return 0;
}