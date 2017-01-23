int main(int argc, char *argv[]) {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();

    // n-by-n random system (likely full rank)
    int n = Integer.parseInt(args[0]);
    double[][] A = new double[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = StdRandom.uniform(1000);
    double[] b = new double[n];
    for (int i = 0; i < n; i++)
        b[i] = StdRandom.uniform(1000);
    test("random " + n + "-by-" + n + " (likely full rank)", A, b);


    // n-by-n random system (likely infeasible)
    A = new double[n][n];
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = StdRandom.uniform(1000);
    for (int i = 0; i < n - 1; i++) {
        double alpha = StdRandom.uniform(11) - 5.0;
        for (int j = 0; j < n; j++) {
            A[n - 1][j] += alpha * A[i][j];
        }
    }
    b = new double[n];
    for (int i = 0; i < n; i++)
        b[i] = StdRandom.uniform(1000);
    test("random " + n + "-by-" + n + " (likely infeasible)", A, b);
    return 0;
}