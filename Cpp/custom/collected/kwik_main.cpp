int main(int argc, char* argv[])
{
    In in{argv[1]};
    int context = utility::safe_convert_integer(argv[1]);

    std::string text = in.readAll().replaceAll("\\s+", " ");
    int n = text.length();

    SuffixArray sa = new SuffixArray(text);

    while (Std_in::hasNextLine()) {
        std::string query = Std_in::read_line();
        for (int i = sa.rank(query); i < n; ++i) {
            int from1 = sa.index(i);
            int to1 = Math.min(n, from1 + query.length());
            if (!query.equals(text.substring(from1, to1))) { break; }
            int from2 = Math.max(0, sa.index(i) - context);
            int to2 = Math.min(n, sa.index(i) + context + query.length());
            Std_out::print_line(text.substring(from2, to2));
        }
        Std_out::print_line();
    }
    return 0;
}