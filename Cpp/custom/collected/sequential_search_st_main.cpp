int main(int argc, char *argv[]) {
    SequentialSearchST<std::string, Integer> st = new SequentialSearchST<std::string, Integer>();
    for (int i = 0; !Std_in::is_empty(); ++i) {
        std::string key = Std_in::read_string();
        st.put(key, i);
    }
    for (String s : st.keys())
        Std_out::print_line(s + " " + st.get(s));
    return 0;
}