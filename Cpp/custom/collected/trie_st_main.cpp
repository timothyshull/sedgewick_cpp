int main(int argc, char *argv[]) {
    TrieST<Integer> st = new TrieST<Integer>();
    for (int i = 0; !Std_in::is_empty(); ++i) {
        std::string key = Std_in::read_string();
        st.put(key, i);
    }

    // print results
    if (st.size() < 100) {
        Std_out::print_line("keys(\"\"):");
        for (String key : st.keys()) {
            Std_out::print_line(key + " " + st.get(key));
        }
        Std_out::print_line();
    }

    Std_out::print_line("longestPrefixOf(\"shellsort\"):");
    Std_out::print_line(st.longestPrefixOf("shellsort"));
    Std_out::print_line();

    Std_out::print_line("longestPrefixOf(\"quicksort\"):");
    Std_out::print_line(st.longestPrefixOf("quicksort"));
    Std_out::print_line();

    Std_out::print_line("keysWithPrefix(\"shor\"):");
    for (String s : st.keysWithPrefix("shor"))
        Std_out::print_line(s);
    Std_out::print_line();

    Std_out::print_line("keysThatMatch(\".he.l.\"):");
    for (String s : st.keysThatMatch(".he.l."))
        Std_out::print_line(s);
    return 0;
}