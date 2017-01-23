int main(int argc, char *argv[]) {
    int V = Integer.parseInt(args[0]);
    int E = Integer.parseInt(args[1]);
    int s = 0, t = V - 1;
    FlowNetwork G = new FlowNetwork(V, E);
    StdOut.println(G);

    // compute maximum flow and minimum cut
    FordFulkerson maxflow = new FordFulkerson(G, s, t);
    StdOut.println("Max flow from " + s + " to " + t);
    for (int v = 0; v < G.V(); v++) {
        for (FlowEdge e : G.adj(v)) {
            if ((v == e.from()) && e.flow() > 0)
                StdOut.println("   " + e);
        }
    }

    // print min-cut
    StdOut.print("Min cut: ");
    for (int v = 0; v < G.V(); v++) {
        if (maxflow.inCut(v)) StdOut.print(v + " ");
    }
    StdOut.println();

    StdOut.println("Max flow value = " + maxflow.value());
    return 0;
}