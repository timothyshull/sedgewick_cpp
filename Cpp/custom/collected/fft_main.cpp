int main(int argc, char *argv[]) {
    int n = utility::safe_convert_integer(argv[1]);
    Complex[] x = new Complex[n];

    // original data
    for (int i = 0; i < n; ++i) {
        x[i] = new Complex(i, 0);
        x[i] = new Complex(Std_random::uniform(-1.0, 1.0), 0);
    }
    show(x, "x");

    // FFT of original data
    Complex[] y = fft(x);
    show(y, "y = fft(x)");

    // take inverse FFT
    Complex[] z = ifft(y);
    show(z, "z = ifft(y)");

    // circular convolution of x with itself
    Complex[] c = cconvolve(x, x);
    show(c, "c = cconvolve(x, x)");

    // linear convolution of x with itself
    Complex[] d = convolve(x, x);
    show(d, "d = convolve(x, x)");
    return 0;
}