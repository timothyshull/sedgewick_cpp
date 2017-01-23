int main(int argc, char* argv[])
{
    double xmin = Double.parseDouble(args[0]);
    double xmax = Double.parseDouble(args[1]);
    double ymin = Double.parseDouble(args[2]);
    double ymax = Double.parseDouble(args[3]);
    int trials = Integer.parseInt(args[4]);

    Interval1D xInterval = new Interval1D(xmin, xmax);
    Interval1D yInterval = new Interval1D(ymin, ymax);
    Interval2D box = new Interval2D(xInterval, yInterval);
    box.draw();

    Counter counter = new Counter("hits");
    for (int t = 0; t < trials; t++) {
        double x = StdRandom.uniform(0.0, 1.0);
        double y = StdRandom.uniform(0.0, 1.0);
        Point2D point = new Point2D(x, y);

        if (box.contains(point)) { counter.increment(); }
        else { point.draw(); }
    }

    StdOut.println(counter);
    StdOut.printf("box area = %.2f\n", box.area());
    return 0;
}