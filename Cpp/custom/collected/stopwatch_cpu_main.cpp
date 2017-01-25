int main(int argc, char *argv[]) {
    int n = utility::safe_convert_integer(argv[1]);

    // sum of square roots of integers from 1 to n using std::sqrt(x).
    StopwatchCPU timer1 = new StopwatchCPU();
    double sum1 = 0.0;
    for (int i = 1; i <= n; ++i) {
        sum1 += std::sqrt(i);
    }
    double time1 = timer1.elapsedTime();
    Std_out::printf("%e (%.2f seconds)\n", sum1, time1);

    // sum of square roots of integers from 1 to n using std::pow(x, 0.5).
    StopwatchCPU timer2 = new StopwatchCPU();
    double sum2 = 0.0;
    for (int i = 1; i <= n; ++i) {
        sum2 += std::pow(i, 0.5);
    }
    double time2 = timer2.elapsedTime();
    Std_out::printf("%e (%.2f seconds)\n", sum2, time2);
    return 0;
}