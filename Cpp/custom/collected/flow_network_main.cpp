int main(int argc, char *argv[]) {
    In in = new In(args[0]);
    FlowNetwork G = new FlowNetwork(in);
    StdOut.println(G);
    return 0;
}