int main(int argc, char *argv[]) {
    TrieST<Integer> st = new TrieST<Integer>();
    for (int i = 0; !StdIn.isEmpty(); i++) {
        String key = StdIn.readString();
        st.put(key, i);
    }

    // print results
    if (st.size() < 100) {
        StdOut.println("keys(\"\"):");
        for (String key : st.keys()) {
            StdOut.println(key + " " + st.get(key));
        }
        StdOut.println();
    }

    StdOut.println("longestPrefixOf(\"shellsort\"):");
    StdOut.println(st.longestPrefixOf("shellsort"));
    StdOut.println();

    StdOut.println("longestPrefixOf(\"quicksort\"):");
    StdOut.println(st.longestPrefixOf("quicksort"));
    StdOut.println();

    StdOut.println("keysWithPrefix(\"shor\"):");
    for (String s : st.keysWithPrefix("shor"))
        StdOut.println(s);
    StdOut.println();

    StdOut.println("keysThatMatch(\".he.l.\"):");
    for (String s : st.keysThatMatch(".he.l."))
        StdOut.println(s);
    return 0;
}