int main(int argc, char *argv[]) {
    double[] a = StdArrayIO.readDouble1D();
    StdOut.printf("       min %10.3f\n", min(a));
    StdOut.printf("      mean %10.3f\n", mean(a));
    StdOut.printf("       max %10.3f\n", max(a));
    StdOut.printf("    stddev %10.3f\n", stddev(a));
    StdOut.printf("       var %10.3f\n", var(a));
    StdOut.printf("   stddevp %10.3f\n", stddevp(a));
    StdOut.printf("      varp %10.3f\n", varp(a));
    return 0;
}