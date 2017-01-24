int main(int argc, char *argv[]) {
    double[] a = StdArrayIO.readDouble1D();
    StdArrayIO.print(a);
    StdOut.println();

    // read and print a matrix of doubles
    double[][] b = StdArrayIO.readDouble2D();
    StdArrayIO.print(b);
    StdOut.println();

    // read and print a matrix of doubles
    boolean[][] d = StdArrayIO.readBoolean2D();
    StdArrayIO.print(d);
    StdOut.println();
    return 0;
}