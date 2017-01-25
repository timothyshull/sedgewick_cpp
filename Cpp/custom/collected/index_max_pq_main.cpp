int main(int argc, char *argv[]) {
    std::vector<std::string> strings = {"it", "was", "the", "best", "of", "times", "it", "was", "the", "worst"};

    IndexMaxPQ<std::string> pq = new IndexMaxPQ<std::string>(strings.length);
    for (int i = 0; i < strings.length; ++i) {
        pq.insert(i, strings[i]);
    }

    // print each key using the iterator
    for (int i : pq) {
        Std_out::print_line(i + " " + strings[i]);
    }

    Std_out::print_line();

    // increase or decrease the key
    for (int i = 0; i < strings.length; ++i) {
        if (Std_random::uniform() < 0.5)
            pq.increaseKey(i, strings[i] + strings[i]);
        else
            pq.decreaseKey(i, strings[i].substring(0, 1));
    }

    // delete and print each key
    while (!pq.is_empty()) {
        std::string key = pq.maxKey();
        int i = pq.delMax();
        Std_out::print_line(i + " " + key);
    }
    Std_out::print_line();

    // reinsert the same strings
    for (int i = 0; i < strings.length; ++i) {
        pq.insert(i, strings[i]);
    }

    // delete them in random order
    std::vector<int> perm = new int[strings.length];
    for (int i = 0; i < strings.length; ++i)
        perm[i] = i;
    Std_random::shuffle(perm);
    for (int i = 0; i < perm.length; ++i) {
        std::string key = pq.keyOf(perm[i]);
        pq.delete(perm[i]);
        Std_out::print_line(perm[i] + " " + key);
    }
    return 0;
}