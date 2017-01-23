int main(int argc, char* argv[])
{
    int n = StdIn.readInt();
    Point2D[]
    points = new Point2D[n];
    for (int i = 0; i < n; i++) {
        int x = StdIn.readInt();
        int y = StdIn.readInt();
        points[i] = new Point2D(x, y);
    }
    GrahamScan graham = new GrahamScan(points);
    for (Point2D p : graham.hull()) {
        StdOut.println(p);
    }
    return 0;
}