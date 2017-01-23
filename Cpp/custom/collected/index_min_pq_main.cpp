int main(int argc, char *argv[]) {
    String[] strings = {"it", "was", "the", "best", "of", "times", "it", "was", "the", "worst"};

    IndexMinPQ<String> pq = new IndexMinPQ<String>(strings.length);
    for (int i = 0; i < strings.length; i++) {
        pq.insert(i, strings[i]);
    }

    // delete and print each key
    while (!pq.isEmpty()) {
        int i = pq.delMin();
        StdOut.println(i + " " + strings[i]);
    }
    StdOut.println();

    // reinsert the same strings
    for (int i = 0; i < strings.length; i++) {
        pq.insert(i, strings[i]);
    }

    // print each key using the iterator
    for (int i : pq) {
        StdOut.println(i + " " + strings[i]);
    }
    while (!pq.isEmpty()) {
        pq.delMin();
    }
    return 0;
}