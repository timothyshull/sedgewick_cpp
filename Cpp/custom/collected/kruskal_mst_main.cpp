int main(int argc, char* argv[])
{
    In in{argv[1]};
    Edge_weighted_graph G = new Edge_weighted_graph(in);
    KruskalMST mst = new KruskalMST(G);
    for (Edge e : mst.edges()) {
        Std_out::print_line(e);
    }
    Std_out::printf("%.5f\n", mst.weight());
    return 0;
}