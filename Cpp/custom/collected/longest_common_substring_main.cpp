int main(int argc, char *argv[]) {
    In in1 = new In(args[0]);
    In in2 = new In(args[1]);
    String s = in1.readAll().trim().replaceAll("\\s+", " ");
    String t = in2.readAll().trim().replaceAll("\\s+", " ");
    StdOut.println("'" + lcs(s, t) + "'");
    return 0;
}