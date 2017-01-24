int main(int argc, char *argv[]) {
    In in{argv[1]};
    FlowNetwork G = new FlowNetwork(in);
    Std_out::print_line(G);
    return 0;
}