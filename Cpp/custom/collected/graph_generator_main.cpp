int main(int argc, char *argv[]) {
    int V = Integer.parseInt(args[0]);
    int E = Integer.parseInt(args[1]);
    int V1 = V / 2;
    int V2 = V - V1;

    StdOut.println("complete graph");
    StdOut.println(complete(V));
    StdOut.println();

    StdOut.println("simple");
    StdOut.println(simple(V, E));
    StdOut.println();

    StdOut.println("Erdos-Renyi");
    double p = (double) E / (V * (V - 1) / 2.0);
    StdOut.println(simple(V, p));
    StdOut.println();

    StdOut.println("complete bipartite");
    StdOut.println(completeBipartite(V1, V2));
    StdOut.println();

    StdOut.println("bipartite");
    StdOut.println(bipartite(V1, V2, E));
    StdOut.println();

    StdOut.println("Erdos Renyi bipartite");
    double q = (double) E / (V1 * V2);
    StdOut.println(bipartite(V1, V2, q));
    StdOut.println();

    StdOut.println("path");
    StdOut.println(path(V));
    StdOut.println();

    StdOut.println("cycle");
    StdOut.println(cycle(V));
    StdOut.println();

    StdOut.println("binary tree");
    StdOut.println(binaryTree(V));
    StdOut.println();

    StdOut.println("tree");
    StdOut.println(tree(V));
    StdOut.println();

    StdOut.println("4-regular");
    StdOut.println(regular(V, 4));
    StdOut.println();

    StdOut.println("star");
    StdOut.println(star(V));
    StdOut.println();

    StdOut.println("wheel");
    StdOut.println(wheel(V));
    StdOut.println();
    return 0;
}