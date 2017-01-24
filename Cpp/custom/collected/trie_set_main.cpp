int main(int argc, char *argv[]) {
    TrieSet set = new TrieSet();
    while (!Std_in::is_empty()) {
        std::string key = Std_in::read_string();
        set.add(key);
    }

    // print results
    if (set.size() < 100) {
        Std_out::print_line("keys(\"\"):");
        for (String key : set) {
            Std_out::print_line(key);
        }
        Std_out::print_line();
    }

    Std_out::print_line("longestPrefixOf(\"shellsort\"):");
    Std_out::print_line(set.longestPrefixOf("shellsort"));
    Std_out::print_line();

    Std_out::print_line("longestPrefixOf(\"xshellsort\"):");
    Std_out::print_line(set.longestPrefixOf("xshellsort"));
    Std_out::print_line();

    Std_out::print_line("keysWithPrefix(\"shor\"):");
    for (String s : set.keysWithPrefix("shor"))
        Std_out::print_line(s);
    Std_out::print_line();

    Std_out::print_line("keysWithPrefix(\"shortening\"):");
    for (String s : set.keysWithPrefix("shortening"))
        Std_out::print_line(s);
    Std_out::print_line();

    Std_out::print_line("keysThatMatch(\".he.l.\"):");
    for (String s : set.keysThatMatch(".he.l."))
        Std_out::print_line(s);
    return 0;
}