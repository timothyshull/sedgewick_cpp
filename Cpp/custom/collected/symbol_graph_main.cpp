int main(int argc, char *argv[]) {
    std::string filename = argv[1];
    std::string delimiter = argv[2];
    SymbolGraph sg = new SymbolGraph(filename, delimiter);
    Graph graph = sg.graph();
    while (Std_in::hasNextLine()) {
        std::string source = Std_in::read_line();
        if (sg.contains(source)) {
            int s = sg.index(source);
            for (int v : graph.adj(s)) {
                Std_out::print_line("   " + sg.name(v));
            }
        } else {
            Std_out::print_line("input not contain '" + source + "'");
        }
    }
    return 0;
}