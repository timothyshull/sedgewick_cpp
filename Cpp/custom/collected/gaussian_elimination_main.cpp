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
    int n = utility::safe_convert_integer(argv[1]);
    std::vector<std::vector<double>> A = new double[n][n];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            A[i][j] = Std_random::uniform(1000);
    std::vector<double> b = new double[n];
    for (int i = 0; i < n; ++i)
        b[i] = Std_random::uniform(1000);

    test(n + "-by-" + n + " (probably nonsingular)", A, b);
    return 0;
}