int main(int argc, char *argv[]) {
    int n = StdIn.readInt();
    Point2D[] points = new Point2D[n];
    for (int i = 0; i < n; i++) {
        double x = StdIn.readDouble();
        double y = StdIn.readDouble();
        points[i] = new Point2D(x, y);
    }
    ClosestPair closest = new ClosestPair(points);
    StdOut.println(closest.distance() + " from " + closest.either() + " to " + closest.other());
    return 0;
}
