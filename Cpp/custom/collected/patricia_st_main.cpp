int main(int argc, char *argv[]) {
    PatriciaST<Integer> st = new PatriciaST<Integer>();
    int limitItem = 1000000;
    int limitPass = 1;
    int countPass = 0;
    boolean ok = true;

    if (args.length > 0) limitItem = Integer.parseInt(args[0]);
    if (args.length > 1) limitPass = Integer.parseInt(args[1]);

    do {
        String[] a = new String[limitItem];
        int[] v = new int[limitItem];

        StdOut.printf("Creating dataset (%d items)...\n", limitItem);
        for (int i = 0; i < limitItem; i++) {
            a[i] = Integer.toString(i, 16);
            v[i] = i;
        }

        StdOut.printf("Shuffling...\n");
        StdRandom.shuffle(v);

        StdOut.printf("Adding (%d items)...\n", limitItem);
        for (int i = 0; i < limitItem; i++)
            st.put(a[v[i]], v[i]);

        int countKeys = 0;
        StdOut.printf("Iterating...\n");
        for (String key : st.keys()) countKeys++;
        StdOut.printf("%d items iterated\n", countKeys);
        if (countKeys != limitItem) ok = false;
        if (countKeys != st.size()) ok = false;

        StdOut.printf("Shuffling...\n");
        StdRandom.shuffle(v);

        int limitDelete = limitItem / 2;
        StdOut.printf("Deleting (%d items)...\n", limitDelete);
        for (int i = 0; i < limitDelete; i++)
            st.delete(a[v[i]]);

        countKeys = 0;
        StdOut.printf("Iterating...\n");
        for (String key : st.keys()) countKeys++;
        StdOut.printf("%d items iterated\n", countKeys);
        if (countKeys != limitItem - limitDelete) ok = false;
        if (countKeys != st.size()) ok = false;

        int countDelete = 0;
        int countRemain = 0;
        StdOut.printf("Checking...\n");
        for (int i = 0; i < limitItem; i++) {
            if (i < limitDelete) {
                if (!st.contains(a[v[i]])) countDelete++;
            } else {
                int val = st.get(a[v[i]]);
                if (val == v[i]) countRemain++;
            }
        }
        StdOut.printf("%d items found and %d (deleted) items missing\n",
                      countRemain, countDelete);
        if (countRemain + countDelete != limitItem) ok = false;
        if (countRemain != st.size()) ok = false;
        if (st.isEmpty()) ok = false;

        StdOut.printf("Deleting the rest (%d items)...\n",
                      limitItem - countDelete);
        for (int i = countDelete; i < limitItem; i++)
            st.delete(a[v[i]]);
        if (!st.isEmpty()) ok = false;

        countPass++;
        if (ok) StdOut.printf("PASS %d TESTS SUCCEEDED\n", countPass);
        else StdOut.printf("PASS %d TESTS FAILED\n", countPass);
    } while (ok && countPass < limitPass);

    if (!ok) throw new java.lang.RuntimeException("TESTS FAILED");
    return 0;
}