int factorial_modulo(int N, int M) {
    if (N == 1) {
        return 1;
    }
    return (N % M) * factorial_modulo(N - 1, M);
}
