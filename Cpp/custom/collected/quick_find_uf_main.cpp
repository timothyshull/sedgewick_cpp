int main(int argc, char *argv[]) {
    int n = Std_in::read_int();
    QuickFindUF uf = new QuickFindUF(n);
    while (!Std_in::is_empty()) {
        int p = Std_in::read_int();
        int q = Std_in::read_int();
        if (uf.connected(p, q)) continue;
        uf.union(p, q);
        Std_out::print_line(p + " " + q);
    }
    Std_out::print_line(uf.count() + " components");
    return 0;
}