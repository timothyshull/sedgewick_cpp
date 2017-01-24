int main(int argc, char *argv[]) {
    std::vector<double> xdata = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> ydata = {5.0, 2.0, 4.0, 1.0};
    Vector x = new Vector(xdata);
    Vector y = new Vector(ydata);

    Std_out::print_line("   x       = " + x);
    Std_out::print_line("   y       = " + y);

    Vector z = x.plus(y);
    Std_out::print_line("   z       = " + z);

    z = z.times(10.0);
    Std_out::print_line(" 10z       = " + z);

    Std_out::print_line("  |x|      = " + x.magnitude());
    Std_out::print_line(" <x, y>    = " + x.dot(y));
    Std_out::print_line("dist(x, y) = " + x.distanceTo(y));
    Std_out::print_line("dir(x)     = " + x.direction());
    return 0;
}