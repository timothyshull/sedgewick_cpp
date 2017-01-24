int main(int argc, char *argv[]) {
    int distinct = 0, words = 0;
    int minlen = utility::safe_convert_integer(argv[1]);
    ST<std::string, Integer> st = new ST<std::string, Integer>();

    // compute frequency counts
    while (!Std_in::is_empty()) {
        std::string key = Std_in::read_string();
        if (key.length() < minlen) continue;
        words++;
        if (st.contains(key)) {
            st.put(key, st.get(key) + 1);
        } else {
            st.put(key, 1);
            distinct++;
        }
    }

    // find a key with the highest frequency count
    std::string max = "";
    st.put(max, 0);
    for (String word : st.keys()) {
        if (st.get(word) > st.get(max))
            max = word;
    }

    Std_out::print_line(max + " " + st.get(max));
    Std_out::print_line("distinct = " + distinct);
    Std_out::print_line("words    = " + words);
    return 0;
}