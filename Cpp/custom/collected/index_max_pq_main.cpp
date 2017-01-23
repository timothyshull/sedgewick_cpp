int main(int argc, char *argv[]) {
    String[] strings = {"it", "was", "the", "best", "of", "times", "it", "was", "the", "worst"};

    IndexMaxPQ<String> pq = new IndexMaxPQ<String>(strings.length);
    for (int i = 0; i < strings.length; i++) {
        pq.insert(i, strings[i]);
    }

    // print each key using the iterator
    for (int i : pq) {
        StdOut.println(i + " " + strings[i]);
    }

    StdOut.println();

    // increase or decrease the key
    for (int i = 0; i < strings.length; i++) {
        if (StdRandom.uniform() < 0.5)
            pq.increaseKey(i, strings[i] + strings[i]);
        else
            pq.decreaseKey(i, strings[i].substring(0, 1));
    }

    // delete and print each key
    while (!pq.isEmpty()) {
        String key = pq.maxKey();
        int i = pq.delMax();
        StdOut.println(i + " " + key);
    }
    StdOut.println();

    // reinsert the same strings
    for (int i = 0; i < strings.length; i++) {
        pq.insert(i, strings[i]);
    }

    // delete them in random order
    int[] perm = new int[strings.length];
    for (int i = 0; i < strings.length; i++)
        perm[i] = i;
    StdRandom.shuffle(perm);
    for (int i = 0; i < perm.length; i++) {
        String key = pq.keyOf(perm[i]);
        pq.delete(perm[i]);
        StdOut.println(perm[i] + " " + key);
    }
    return 0;
}