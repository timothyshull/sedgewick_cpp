int main(int argc, char *argv[]) {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();

    // n-by-n random system
    int n = Integer.parseInt(args[0]);
    double[][] A = new double[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = StdRandom.uniform(1000);
    double[] b = new double[n];
    for (int i = 0; i < n; i++)
        b[i] = StdRandom.uniform(1000);

    test(n + "-by-" + n + " (probably nonsingular)", A, b);
    return 0;
}