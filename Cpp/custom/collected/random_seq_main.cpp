int main(int argc, char *argv[]) {
    int n = utility::safe_convert_integer(argv[1]);

    // for backward compatibility with Intro to Programming in Java version of RandomSeq
    if (argc == 2) {
        // generate and print n numbers between 0.0 and 1.0
        for (int i = 0; i < n; ++i) {
            double x = Std_random::uniform();
            Std_out::print_line(x);
        }
    } else if (argc == 4) {
        double lo = Double.parseDouble(argv[1]);
        double hi = Double.parseDouble(argv[2]);

        // generate and print n numbers between lo and hi
        for (int i = 0; i < n; ++i) {
            double x = Std_random::uniform(lo, hi);
            Std_out::printf("%.2f\n", x);
        }
    } else {
        throw new IllegalArgumentException("Invalid number of arguments");
    }
    return 0;
}