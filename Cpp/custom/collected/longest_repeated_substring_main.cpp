int main(int argc, char *argv[]) {
    String text = StdIn.readAll().replaceAll("\\s+", " ");
    StdOut.println("'" + lrs(text) + "'");
    return 0;
}