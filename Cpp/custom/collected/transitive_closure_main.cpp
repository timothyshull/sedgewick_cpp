int main(int argc, char *argv[]) {
    In in{argv[1]};
    Digraph G{in};

    TransitiveClosure tc = new TransitiveClosure(G);

    // print header
    Std_out::print("     ");
    for (int v = 0; v < G.num_vertices(); ++v)
        Std_out::printf("%3d", v);
    Std_out::print_line();
    Std_out::print_line("--------------------------------------------");

    // print transitive closure
    for (int v = 0; v < G.num_vertices(); ++v) {
        Std_out::printf("%3d: ", v);
        for (int w = 0; w < G.num_vertices(); ++w) {
            if (tc.reachable(v, w)) Std_out::printf("  T");
            else Std_out::printf("   ");
        }
        Std_out::print_line();
    }
    return 0;
}