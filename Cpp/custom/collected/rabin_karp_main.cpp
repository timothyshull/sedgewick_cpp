int main(int argc, char *argv[]) {
    String pat = args[0];
    String txt = args[1];

    RabinKarp searcher = new RabinKarp(pat);
    int offset = searcher.search(txt);

    // print results
    StdOut.println("text:    " + txt);

    // from brute force search method 1
    StdOut.print("pattern: ");
    for (int i = 0; i < offset; i++)
        StdOut.print(" ");
    StdOut.println(pat);
    return 0;
}