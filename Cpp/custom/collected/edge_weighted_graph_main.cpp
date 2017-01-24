int main(int argc, char *argv[]) {
    In in{argv[1]};
    Edge_weighted_graph G = new Edge_weighted_graph(in);
    Std_out::print_line(G);
    return 0;
}