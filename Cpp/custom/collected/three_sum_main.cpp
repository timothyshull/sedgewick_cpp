int main(int argc, char *argv[]) {
    In in = new In(args[0]);
    int[] a = in.readAllInts();

    Stopwatch timer = new Stopwatch();
    int count = count(a);
    StdOut.println("elapsed time = " + timer.elapsedTime());
    StdOut.println(count);
    return 0;
}