int main(int argc, char* argv[])
{
    double xmin = Double.parseDouble(argv[1]);
    double xmax = Double.parseDouble(argv[2]);
    double ymin = Double.parseDouble(argv[3]);
    double ymax = Double.parseDouble(argv[4]);
    int trials = utility::safe_convert_integer(argv[5]);

    Interval1D xInterval = new Interval1D(xmin, xmax);
    Interval1D yInterval = new Interval1D(ymin, ymax);
    Interval2D box = new Interval2D(xInterval, yInterval);
    box.draw();

    Counter counter = new Counter("hits");
    for (int t = 0; t < trials; ++t) {
        double x = Std_random::uniform(0.0, 1.0);
        double y = Std_random::uniform(0.0, 1.0);
        Point_2d point = new Point_2d(x, y);

        if (box.contains(point)) { counter.increment(); }
        else { point.draw(); }
    }

    Std_out::print_line(counter);
    Std_out::printf("box area = %.2f\n", box.area());
    return 0;
}