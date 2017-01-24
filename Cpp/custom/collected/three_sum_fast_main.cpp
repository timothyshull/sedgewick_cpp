int main(int argc, char *argv[]) {
    In in = new In(args[0]);
    int[] a = in.readAllInts();
    int count = count(a);
    StdOut.println(count);
    return 0;
}