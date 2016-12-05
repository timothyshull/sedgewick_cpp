using Item = int;

// a[l] ... a[r] -> a[l] ... a[m], a[m + 1] ... a[r]

//Item max(Item a[], int l, int r) {
//    if (l == r) {
//        return a[l];
//    }
//    int m = (l + r) / 2;
//    Item u = max(a, l, m);
//    Item v = max(a, m + l, r);
//    if (u > v) {
//        return u;
//    } else {
//        return v;
//    }
//}

// so ugly
Item max(Item a[], int size, int k) {
    if (k) {
        int section_size = size / k;
        int remainder = size % k;
        int max = 0;
        int outer_index = 0;
        for (int i = 0; i < k; i++) {
            int lsz = section_size;
            if (remainder) {
                lsz = section_size + 1;
                remainder--;
            }
            Item tmp[size];
            for (int j = 0; j < lsz; j++) {
                tmp[i] = a[i + outer_index];
            }
            outer_index += lsz;
            int u = max(tmp, lsz, 0);
            if (u > max) {
                max = u;
            }
        }
        return max;
    } else {
        Item max = 0;
        for (int i = 0; i < size; i++) {
            if (a[i] > max) {
                max = a[i];
            }
        }
        return max;
    }
}