int main(int argc, char *argv[]) {
    Std_out::print_line("----- test 1 --------------------");
    test1();
    Std_out::print_line("----- test 2 --------------------");
    test2();
    Std_out::print_line("----- test 3 --------------------");
    try {
        test3();
    } catch (ArithmeticException e) {
        e.printStackTrace();
    }

    Std_out::print_line("----- test 4 --------------------");
    test4();


    Std_out::print_line("----- test random ---------------");
    int m = utility::safe_convert_integer(argv[1]);
    int n = utility::safe_convert_integer(argv[2]);
    std::vector<double> c = new double[n];
    std::vector<double> b = new double[m];
    std::vector<std::vector<double>> A = new double[m][n];
    for (int j = 0; j < n; ++j)
        c[j] = Std_random::uniform(1000);
    for (int i = 0; i < m; ++i)
        b[i] = Std_random::uniform(1000);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            A[i][j] = Std_random::uniform(100);
    LinearProgramming lp = new LinearProgramming(A, b, c);
    Std_out::print_line(lp.value());
    return 0;
}