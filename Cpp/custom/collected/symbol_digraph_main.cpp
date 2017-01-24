int main(int argc, char *argv[]) {
    std::string filename = argv[1];
    std::string delimiter = argv[2];
    SymbolDigraph sg = new SymbolDigraph(filename, delimiter);
    Digraph graph = sg.digraph();
    while (!Std_in::is_empty()) {
        std::string t = Std_in::read_line();
        for (int v : graph.adj(sg.index(t))) {
            Std_out::print_line("   " + sg.name(v));
        }
    }
    return 0;
}