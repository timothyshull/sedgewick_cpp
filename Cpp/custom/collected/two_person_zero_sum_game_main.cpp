int main(int argc, char *argv[]) {
    test1();
    test2();
    test3();
    test4();
    test5();

    int m = Integer.parseInt(args[0]);
    int n = Integer.parseInt(args[1]);
    double[][] payoff = new double[m][n];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            payoff[i][j] = StdRandom.uniform(-0.5, 0.5);
    test("random " + m + "-by-" + n, payoff);
    return 0;
}