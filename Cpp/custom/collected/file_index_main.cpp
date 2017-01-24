int main(int argc, char *argv[]) {
    ST<std::string, Set<File>> st = new ST<std::string, Set<File>>();

    // create inverted index of all files
    Std_out::print_line("Indexing files");
    for (String filename : argv) {
        Std_out::print_line("  " + filename);
        File file = new File(filename);
        In in = new In(file);
        while (!in.is_empty()) {
            std::string word = in.read_string();
            if (!st.contains(word)) st.put(word, new Set<File>());
            Set<File> set = st.get(word);
            set.add(file);
        }
    }


    // read queries from standard input, one per line
    while (!Std_in::is_empty()) {
        std::string query = Std_in::read_string();
        if (st.contains(query)) {
            Set<File> set = st.get(query);
            for (File file : set) {
                Std_out::print_line("  " + file.getName());
            }
        }
    }
    return 0;
}