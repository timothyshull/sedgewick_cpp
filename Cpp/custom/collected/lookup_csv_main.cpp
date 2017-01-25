int main(int argc, char *argv[]) {
    int keyField = utility::safe_convert_integer(argv[1]);
    int valField = utility::safe_convert_integer(argv[2]);

    // symbol table
    ST<std::string, std::string> st = new ST<std::string, std::string>();

    // read in the data from csv file
    In in{argv[1]};
    while (in.hasNextLine()) {
        std::string line = in.read_line();
        std::vector<std::string> tokens = line.split(",");
        std::string key = tokens[keyField];
        std::string val = tokens[valField];
        st.put(key, val);
    }

    while (!Std_in::is_empty()) {
        std::string s = Std_in::read_string();
        if (st.contains(s)) Std_out::print_line(st.get(s));
        else Std_out::print_line("Not found");
    }
    return 0;
}