int main(int argc, char *argv[]) {
    for (int n = 250; true; n += n) {
        double time = timeTrial(n);
        StdOut.printf("%7d %5.1f\n", n, time);
    }
    return 0;
}