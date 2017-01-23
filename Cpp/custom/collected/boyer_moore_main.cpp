int main(int argc, char *argv[]) {
    String pat = args[0];
    String txt = args[1];
    char[] pattern = pat.toCharArray();
    char[] text = txt.toCharArray();

    BoyerMoore boyermoore1 = new BoyerMoore(pat);
    BoyerMoore boyermoore2 = new BoyerMoore(pattern, 256);
    int offset1 = boyermoore1.search(txt);
    int offset2 = boyermoore2.search(text);

    // print results
    StdOut.println("text:    " + txt);

    StdOut.print("pattern: ");
    for (int i = 0; i < offset1; i++)
        StdOut.print(" ");
    StdOut.println(pat);

    StdOut.print("pattern: ");
    for (int i = 0; i < offset2; i++)
        StdOut.print(" ");
    StdOut.println(pat);
    return 0;
}