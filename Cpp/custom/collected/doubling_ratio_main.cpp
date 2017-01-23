int main(int argc, char *argv[]) {
    double prev = timeTrial(125);
    for (int n = 250; true; n += n) {
        double time = timeTrial(n);
        StdOut.printf("%6d %7.1f %5.1f\n", n, time, time / prev);
        prev = time;
    }
    return 0;
}