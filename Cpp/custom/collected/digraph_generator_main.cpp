int main(int argc, char *argv[]) {
    int V = Integer.parseInt(args[0]);
    int E = Integer.parseInt(args[1]);
    StdOut.println("complete graph");
    StdOut.println(complete(V));
    StdOut.println();

    StdOut.println("simple");
    StdOut.println(simple(V, E));
    StdOut.println();

    StdOut.println("path");
    StdOut.println(path(V));
    StdOut.println();

    StdOut.println("cycle");
    StdOut.println(cycle(V));
    StdOut.println();

    StdOut.println("Eulierian path");
    StdOut.println(eulerianPath(V, E));
    StdOut.println();

    StdOut.println("Eulierian cycle");
    StdOut.println(eulerianCycle(V, E));
    StdOut.println();

    StdOut.println("binary tree");
    StdOut.println(binaryTree(V));
    StdOut.println();

    StdOut.println("tournament");
    StdOut.println(tournament(V));
    StdOut.println();

    StdOut.println("DAG");
    StdOut.println(dag(V, E));
    StdOut.println();

    StdOut.println("rooted-in DAG");
    StdOut.println(rootedInDAG(V, E));
    StdOut.println();

    StdOut.println("rooted-out DAG");
    StdOut.println(rootedOutDAG(V, E));
    StdOut.println();

    StdOut.println("rooted-in tree");
    StdOut.println(rootedInTree(V));
    StdOut.println();

    StdOut.println("rooted-out DAG");
    StdOut.println(rootedOutTree(V));
    StdOut.println();
    return 0;
}