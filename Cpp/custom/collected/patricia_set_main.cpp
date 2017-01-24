int main(int argc, char *argv[]) {
    PatriciaSET set = new PatriciaSET();
    int limitItem = 1000000;
    int limitPass = 1;
    int countPass = 0;
    boolean ok = true;

    if (args.length > 0) limitItem = Integer.parseInt(args[0]);
    if (args.length > 1) limitPass = Integer.parseInt(args[1]);

    do {
        String[] a = new String[limitItem];

        StdOut.printf("Creating dataset (%d items)...\n", limitItem);
        for (int i = 0; i < limitItem; i++)
            a[i] = Integer.toString(i, 16);

        StdOut.printf("Shuffling...\n");
        StdRandom.shuffle(a);

        StdOut.printf("Adding (%d items)...\n", limitItem);
        for (int i = 0; i < limitItem; i++)
            set.add(a[i]);

        int countItems = 0;
        StdOut.printf("Iterating...\n");
        for (String key : set) countItems++;
        StdOut.printf("%d items iterated\n", countItems);
        if (countItems != limitItem) ok = false;
        if (countItems != set.size()) ok = false;

        StdOut.printf("Shuffling...\n");
        StdRandom.shuffle(a);

        int limitDelete = limitItem / 2;
        StdOut.printf("Deleting (%d items)...\n", limitDelete);
        for (int i = 0; i < limitDelete; i++)
            set.delete(a[i]);

        countItems = 0;
        StdOut.printf("Iterating...\n");
        for (String key : set) countItems++;
        StdOut.printf("%d items iterated\n", countItems);
        if (countItems != limitItem - limitDelete) ok = false;
        if (countItems != set.size()) ok = false;

        int countDelete = 0;
        int countRemain = 0;
        StdOut.printf("Checking...\n");
        for (int i = 0; i < limitItem; i++) {
            if (i < limitDelete) {
                if (!set.contains(a[i])) countDelete++;
            } else {
                if (set.contains(a[i])) countRemain++;
            }
        }
        StdOut.printf("%d items found and %d (deleted) items missing\n",
                      countRemain, countDelete);
        if (countRemain + countDelete != limitItem) ok = false;
        if (countRemain != set.size()) ok = false;
        if (set.isEmpty()) ok = false;

        StdOut.printf("Deleting the rest (%d items)...\n",
                      limitItem - countDelete);
        for (int i = countDelete; i < limitItem; i++)
            set.delete(a[i]);
        if (!set.isEmpty()) ok = false;

        countPass++;
        if (ok) StdOut.printf("PASS %d TESTS SUCCEEDED\n", countPass);
        else StdOut.printf("PASS %d TESTS FAILED\n", countPass);
    } while (ok && countPass < limitPass);

    if (!ok) throw new java.lang.RuntimeException("TESTS FAILED");
    return 0;
}