int main(int argc, char *argv[]) {
    std::string s = Std_in::readAll().replaceAll("\n", " ").trim();
    SuffixArrayX suffix1 = new SuffixArrayX(s);
    SuffixArray suffix2 = new SuffixArray(s);
    bool check = true;
    for (int i = 0; check && i < s.length(); ++i) {
        if (suffix1.index(i) != suffix2.index(i)) {
            Std_out::print_line("suffix1(" + i + ") = " + suffix1.index(i));
            Std_out::print_line("suffix2(" + i + ") = " + suffix2.index(i));
            std::string ith = "\"" + s.substring(suffix1.index(i), Math.min(suffix1.index(i) + 50, s.length())) + "\"";
            std::string jth = "\"" + s.substring(suffix2.index(i), Math.min(suffix2.index(i) + 50, s.length())) + "\"";
            Std_out::print_line(ith);
            Std_out::print_line(jth);
            check = false;
        }
    }

    Std_out::print_line("  i ind lcp rnk  select");
    Std_out::print_line("---------------------------");

    for (int i = 0; i < s.length(); ++i) {
        int index = suffix2.index(i);
        std::string ith = "\"" + s.substring(index, Math.min(index + 50, s.length())) + "\"";
        int rank = suffix2.rank(s.substring(index));
        assert s.substring(index).equals(suffix2.select(i));
        if (i == 0) {
            Std_out::printf("%3d %3d %3s %3d  %s\n", i, index, "-", rank, ith);
        } else {
            // int lcp  = suffix.lcp(suffix2.index(i), suffix2.index(i-1));
            int lcp = suffix2.lcp(i);
            Std_out::printf("%3d %3d %3d %3d  %s\n", i, index, lcp, rank, ith);
        }
    }
    return 0;
}