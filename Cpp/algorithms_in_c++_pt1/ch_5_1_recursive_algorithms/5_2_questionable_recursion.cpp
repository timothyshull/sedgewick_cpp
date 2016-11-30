int puzzle(int N) {
    if (N == 1) return 1;
    if (N % 2 == 0)
        return puzzle(N / 2);
    else return puzzle(3 * N + 1);
}

// 1
// 2 -> 1
// 3 -> 10 -> 5 -> 16 -> 8 -> 25 ...
// 4 -> 2 -> 1
// 5 -> 16 -> 8 -> 25 -> 76 ->