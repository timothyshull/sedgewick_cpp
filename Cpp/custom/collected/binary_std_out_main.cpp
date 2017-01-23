int main(int argc, char *argv[]) {
    int m = Integer.parseInt(args[0]);

    // write n integers to binary standard output
    for (int i = 0; i < m; i++) {
        BinaryStdOut.write(i);
    }
    BinaryStdOut.flush();
    return 0;
}