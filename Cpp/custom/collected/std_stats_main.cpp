int main(int argc, char *argv[]) {
    std::vector<double> a = StdArrayIO.read_double1D();
    Std_out::printf("       min %10.3f\n", min(a));
    Std_out::printf("      mean %10.3f\n", mean(a));
    Std_out::printf("       max %10.3f\n", max(a));
    Std_out::printf("    stddev %10.3f\n", stddev(a));
    Std_out::printf("       var %10.3f\n", var(a));
    Std_out::printf("   stddevp %10.3f\n", stddevp(a));
    Std_out::printf("      varp %10.3f\n", varp(a));
    return 0;
}