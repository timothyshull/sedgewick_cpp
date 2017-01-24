int main(int argc, char *argv[]) {
    String s = StdIn.readAll().replaceAll("\\s+", " ").trim();
    SuffixArray suffix = new SuffixArray(s);

    // StdOut.println("rank(" + args[0] + ") = " + suffix.rank(args[0]));

    StdOut.println("  i ind lcp rnk select");
    StdOut.println("---------------------------");

    for (int i = 0; i < s.length(); i++) {
        int index = suffix.index(i);
        String ith = "\"" + s.substring(index, Math.min(index + 50, s.length())) + "\"";
        assert s.substring(index).equals(suffix.select(i));
        int rank = suffix.rank(s.substring(index));
        if (i == 0) {
            StdOut.printf("%3d %3d %3s %3d %s\n", i, index, "-", rank, ith);
        } else {
            int lcp = suffix.lcp(i);
            StdOut.printf("%3d %3d %3d %3d %s\n", i, index, lcp, rank, ith);
        }
    }
    return 0;
}