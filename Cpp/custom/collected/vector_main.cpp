int main(int argc, char *argv[]) {
    double[] xdata = {1.0, 2.0, 3.0, 4.0};
    double[] ydata = {5.0, 2.0, 4.0, 1.0};
    Vector x = new Vector(xdata);
    Vector y = new Vector(ydata);

    StdOut.println("   x       = " + x);
    StdOut.println("   y       = " + y);

    Vector z = x.plus(y);
    StdOut.println("   z       = " + z);

    z = z.times(10.0);
    StdOut.println(" 10z       = " + z);

    StdOut.println("  |x|      = " + x.magnitude());
    StdOut.println(" <x, y>    = " + x.dot(y));
    StdOut.println("dist(x, y) = " + x.distanceTo(y));
    StdOut.println("dir(x)     = " + x.direction());
    return 0;
}