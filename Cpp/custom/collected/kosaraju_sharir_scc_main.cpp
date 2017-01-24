int main(int argc, char* argv[])
{
    In in{argv[1]};
    Digraph G{in};
    KosarajuSharirSCC scc = new KosarajuSharirSCC(G);

    int m = scc.count();
    Std_out::print_line(m + " components");

    Queue<Integer>[] components = (Queue<Integer>[])
    new Queue[m];
    for (int i = 0; i < m; ++i) {
        components[i] = new Queue<Integer>();
    }
    for (int v = 0; v < G.num_vertices(); ++v) {
        components[scc.id(v)].enqueue(v);
    }

    for (int i = 0; i < m; ++i) {
        for (int v : components[i]) {
            Std_out::print(v + " ");
        }
        Std_out::print_line();
    }
    return 0;
}