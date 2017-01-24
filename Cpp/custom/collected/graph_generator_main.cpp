int main(int argc, char *argv[]) {
    int V = utility::safe_convert_integer(argv[1]);
    int E = utility::safe_convert_integer(argv[2]);
    int V1 = V / 2;
    int V2 = V - V1;

    Std_out::print_line("complete graph");
    Std_out::print_line(complete(V));
    Std_out::print_line();

    Std_out::print_line("simple");
    Std_out::print_line(simple(V, E));
    Std_out::print_line();

    Std_out::print_line("Erdos-Renyi");
    double p = (double) E / (V * (V - 1) / 2.0);
    Std_out::print_line(simple(V, p));
    Std_out::print_line();

    Std_out::print_line("complete bipartite");
    Std_out::print_line(completeBipartite(V1, V2));
    Std_out::print_line();

    Std_out::print_line("bipartite");
    Std_out::print_line(bipartite(V1, V2, E));
    Std_out::print_line();

    Std_out::print_line("Erdos Renyi bipartite");
    double q = (double) E / (V1 * V2);
    Std_out::print_line(bipartite(V1, V2, q));
    Std_out::print_line();

    Std_out::print_line("path");
    Std_out::print_line(path(V));
    Std_out::print_line();

    Std_out::print_line("cycle");
    Std_out::print_line(cycle(V));
    Std_out::print_line();

    Std_out::print_line("binary tree");
    Std_out::print_line(binaryTree(V));
    Std_out::print_line();

    Std_out::print_line("tree");
    Std_out::print_line(tree(V));
    Std_out::print_line();

    Std_out::print_line("4-regular");
    Std_out::print_line(regular(V, 4));
    Std_out::print_line();

    Std_out::print_line("star");
    Std_out::print_line(star(V));
    Std_out::print_line();

    Std_out::print_line("wheel");
    Std_out::print_line(wheel(V));
    Std_out::print_line();
    return 0;
}