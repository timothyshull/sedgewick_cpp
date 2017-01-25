int main(int argc, char *argv[]) {
    std::vector<std::string> strings = {"it", "was", "the", "best", "of", "times", "it", "was", "the", "worst"};

    IndexMinPQ<std::string> pq = new IndexMinPQ<std::string>(strings.length);
    for (int i = 0; i < strings.length; ++i) {
        pq.insert(i, strings[i]);
    }

    // delete and print each key
    while (!pq.is_empty()) {
        int i = pq.delMin();
        Std_out::print_line(i + " " + strings[i]);
    }
    Std_out::print_line();

    // reinsert the same strings
    for (int i = 0; i < strings.length; ++i) {
        pq.insert(i, strings[i]);
    }

    // print each key using the iterator
    for (int i : pq) {
        Std_out::print_line(i + " " + strings[i]);
    }
    while (!pq.is_empty()) {
        pq.delMin();
    }
    return 0;
}