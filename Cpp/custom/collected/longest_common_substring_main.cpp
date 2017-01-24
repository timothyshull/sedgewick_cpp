int main(int argc, char *argv[]) {
    In in1 = new In(argv[1]);
    In in2 = new In(argv[2]);
    std::string s = in1.readAll().trim().replaceAll("\\s+", " ");
    std::string t = in2.readAll().trim().replaceAll("\\s+", " ");
    Std_out::print_line("'" + lcs(s, t) + "'");
    return 0;
}