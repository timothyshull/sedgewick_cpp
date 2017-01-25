int main(int argc, char *argv[]) {
    PatriciaST<Integer> st = new PatriciaST<Integer>();
    int limitItem = 1000000;
    int limitPass = 1;
    int countPass = 0;
    bool ok = true;

    if (argc > 0) limitItem = utility::safe_convert_integer(argv[1]);
    if (argc > 1) limitPass = utility::safe_convert_integer(argv[2]);

    do {
        std::vector<std::string> a = new String[limitItem];
        std::vector<int> v = new int[limitItem];

        Std_out::printf("Creating dataset (%d items)...\n", limitItem);
        for (int i = 0; i < limitItem; ++i) {
            a[i] = Integer.to_string(i, 16);
            v[i] = i;
        }

        Std_out::printf("Shuffling...\n");
        Std_random::shuffle(v);

        Std_out::printf("Adding (%d items)...\n", limitItem);
        for (int i = 0; i < limitItem; ++i)
            st.put(a[v[i]], v[i]);

        int countKeys = 0;
        Std_out::printf("Iterating...\n");
        for (String key : st.keys()) countKeys++;
        Std_out::printf("%d items iterated\n", countKeys);
        if (countKeys != limitItem) ok = false;
        if (countKeys != st.size()) ok = false;

        Std_out::printf("Shuffling...\n");
        Std_random::shuffle(v);

        int limitDelete = limitItem / 2;
        Std_out::printf("Deleting (%d items)...\n", limitDelete);
        for (int i = 0; i < limitDelete; ++i)
            st.delete(a[v[i]]);

        countKeys = 0;
        Std_out::printf("Iterating...\n");
        for (String key : st.keys()) countKeys++;
        Std_out::printf("%d items iterated\n", countKeys);
        if (countKeys != limitItem - limitDelete) ok = false;
        if (countKeys != st.size()) ok = false;

        int countDelete = 0;
        int countRemain = 0;
        Std_out::printf("Checking...\n");
        for (int i = 0; i < limitItem; ++i) {
            if (i < limitDelete) {
                if (!st.contains(a[v[i]])) countDelete++;
            } else {
                int val = st.get(a[v[i]]);
                if (val == v[i]) countRemain++;
            }
        }
        Std_out::printf("%d items found and %d (deleted) items missing\n",
                      countRemain, countDelete);
        if (countRemain + countDelete != limitItem) ok = false;
        if (countRemain != st.size()) ok = false;
        if (st.is_empty()) ok = false;

        Std_out::printf("Deleting the rest (%d items)...\n",
                      limitItem - countDelete);
        for (int i = countDelete; i < limitItem; ++i)
            st.delete(a[v[i]]);
        if (!st.is_empty()) ok = false;

        countPass++;
        if (ok) Std_out::printf("PASS %d TESTS SUCCEEDED\n", countPass);
        else Std_out::printf("PASS %d TESTS FAILED\n", countPass);
    } while (ok && countPass < limitPass);

    if (!ok) throw new java.lang.RuntimeException("TESTS FAILED");
    return 0;
}