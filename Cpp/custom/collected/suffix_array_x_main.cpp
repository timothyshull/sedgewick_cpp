int main(int argc, char *argv[]) {
    String s = StdIn.readAll().replaceAll("\n", " ").trim();
    SuffixArrayX suffix1 = new SuffixArrayX(s);
    SuffixArray suffix2 = new SuffixArray(s);
    boolean check = true;
    for (int i = 0; check && i < s.length(); i++) {
        if (suffix1.index(i) != suffix2.index(i)) {
            StdOut.println("suffix1(" + i + ") = " + suffix1.index(i));
            StdOut.println("suffix2(" + i + ") = " + suffix2.index(i));
            String ith = "\"" + s.substring(suffix1.index(i), Math.min(suffix1.index(i) + 50, s.length())) + "\"";
            String jth = "\"" + s.substring(suffix2.index(i), Math.min(suffix2.index(i) + 50, s.length())) + "\"";
            StdOut.println(ith);
            StdOut.println(jth);
            check = false;
        }
    }

    StdOut.println("  i ind lcp rnk  select");
    StdOut.println("---------------------------");

    for (int i = 0; i < s.length(); i++) {
        int index = suffix2.index(i);
        String ith = "\"" + s.substring(index, Math.min(index + 50, s.length())) + "\"";
        int rank = suffix2.rank(s.substring(index));
        assert s.substring(index).equals(suffix2.select(i));
        if (i == 0) {
            StdOut.printf("%3d %3d %3s %3d  %s\n", i, index, "-", rank, ith);
        } else {
            // int lcp  = suffix.lcp(suffix2.index(i), suffix2.index(i-1));
            int lcp = suffix2.lcp(i);
            StdOut.printf("%3d %3d %3d %3d  %s\n", i, index, lcp, rank, ith);
        }
    }
    return 0;
}