int main(int argc, char *argv[]) {
    PatriciaSet set = new PatriciaSet();
    int limitItem = 1000000;
    int limitPass = 1;
    int countPass = 0;
    bool ok = true;

    if (argc > 0) limitItem = utility::safe_convert_integer(argv[1]);
    if (argc > 1) limitPass = utility::safe_convert_integer(argv[2]);

    do {
        String[] a = new String[limitItem];

        Std_out::printf("Creating dataset (%d items)...\n", limitItem);
        for (int i = 0; i < limitItem; ++i)
            a[i] = Integer.to_string(i, 16);

        Std_out::printf("Shuffling...\n");
        Std_random::shuffle(a);

        Std_out::printf("Adding (%d items)...\n", limitItem);
        for (int i = 0; i < limitItem; ++i)
            set.add(a[i]);

        int countItems = 0;
        Std_out::printf("Iterating...\n");
        for (String key : set) countItems++;
        Std_out::printf("%d items iterated\n", countItems);
        if (countItems != limitItem) ok = false;
        if (countItems != set.size()) ok = false;

        Std_out::printf("Shuffling...\n");
        Std_random::shuffle(a);

        int limitDelete = limitItem / 2;
        Std_out::printf("Deleting (%d items)...\n", limitDelete);
        for (int i = 0; i < limitDelete; ++i)
            set.delete(a[i]);

        countItems = 0;
        Std_out::printf("Iterating...\n");
        for (String key : set) countItems++;
        Std_out::printf("%d items iterated\n", countItems);
        if (countItems != limitItem - limitDelete) ok = false;
        if (countItems != set.size()) ok = false;

        int countDelete = 0;
        int countRemain = 0;
        Std_out::printf("Checking...\n");
        for (int i = 0; i < limitItem; ++i) {
            if (i < limitDelete) {
                if (!set.contains(a[i])) countDelete++;
            } else {
                if (set.contains(a[i])) countRemain++;
            }
        }
        Std_out::printf("%d items found and %d (deleted) items missing\n",
                      countRemain, countDelete);
        if (countRemain + countDelete != limitItem) ok = false;
        if (countRemain != set.size()) ok = false;
        if (set.is_empty()) ok = false;

        Std_out::printf("Deleting the rest (%d items)...\n",
                      limitItem - countDelete);
        for (int i = countDelete; i < limitItem; ++i)
            set.delete(a[i]);
        if (!set.is_empty()) ok = false;

        countPass++;
        if (ok) Std_out::printf("PASS %d TESTS SUCCEEDED\n", countPass);
        else Std_out::printf("PASS %d TESTS FAILED\n", countPass);
    } while (ok && countPass < limitPass);

    if (!ok) throw new java.lang.RuntimeException("TESTS FAILED");
    return 0;
}