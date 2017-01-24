int main(int argc, char *argv[]) {
    TrieSET set = new TrieSET();
    while (!StdIn.isEmpty()) {
        String key = StdIn.readString();
        set.add(key);
    }

    // print results
    if (set.size() < 100) {
        StdOut.println("keys(\"\"):");
        for (String key : set) {
            StdOut.println(key);
        }
        StdOut.println();
    }

    StdOut.println("longestPrefixOf(\"shellsort\"):");
    StdOut.println(set.longestPrefixOf("shellsort"));
    StdOut.println();

    StdOut.println("longestPrefixOf(\"xshellsort\"):");
    StdOut.println(set.longestPrefixOf("xshellsort"));
    StdOut.println();

    StdOut.println("keysWithPrefix(\"shor\"):");
    for (String s : set.keysWithPrefix("shor"))
        StdOut.println(s);
    StdOut.println();

    StdOut.println("keysWithPrefix(\"shortening\"):");
    for (String s : set.keysWithPrefix("shortening"))
        StdOut.println(s);
    StdOut.println();

    StdOut.println("keysThatMatch(\".he.l.\"):");
    for (String s : set.keysThatMatch(".he.l."))
        StdOut.println(s);
    return 0;
}