int main(int argc, char *argv[]) {
    StdOut.println("----- test 1 --------------------");
    test1();
    StdOut.println("----- test 2 --------------------");
    test2();
    StdOut.println("----- test 3 --------------------");
    try {
        test3();
    } catch (ArithmeticException e) {
        e.printStackTrace();
    }

    StdOut.println("----- test 4 --------------------");
    test4();


    StdOut.println("----- test random ---------------");
    int m = Integer.parseInt(args[0]);
    int n = Integer.parseInt(args[1]);
    double[] c = new double[n];
    double[] b = new double[m];
    double[][] A = new double[m][n];
    for (int j = 0; j < n; j++)
        c[j] = StdRandom.uniform(1000);
    for (int i = 0; i < m; i++)
        b[i] = StdRandom.uniform(1000);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = StdRandom.uniform(100);
    LinearProgramming lp = new LinearProgramming(A, b, c);
    StdOut.println(lp.value());
    return 0;
}