int main(int argc, char *argv[]) {
    std::string filename = argv[1];
    std::string separator = argv[2];
    In in = new In(filename);

    ST<std::string, Queue<std::string>> st = new ST<std::string, Queue<std::string>>();
    ST<std::string, Queue<std::string>> ts = new ST<std::string, Queue<std::string>>();

    while (in.hasNextLine()) {
        std::string line = in.read_line();
        String[] fields = line.split(separator);
        std::string key = fields[0];
        for (int i = 1; i < fields.length; ++i) {
            std::string val = fields[i];
            if (!st.contains(key)) st.put(key, new Queue<std::string>());
            if (!ts.contains(val)) ts.put(val, new Queue<std::string>());
            st.get(key).enqueue(val);
            ts.get(val).enqueue(key);
        }
    }

    Std_out::print_line("Done indexing");

    // read queries from standard input, one per line
    while (!Std_in::is_empty()) {
        std::string query = Std_in::read_line();
        if (st.contains(query))
            for (String vals : st.get(query))
                Std_out::print_line("  " + vals);
        if (ts.contains(query))
            for (String keys : ts.get(query))
                Std_out::print_line("  " + keys);
    }
    return 0;
}