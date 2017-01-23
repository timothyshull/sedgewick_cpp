int main(int argc, char *argv[]) {
    int n = StdIn.readInt();
    Point2D[] points = new Point2D[n];
    for (int i = 0; i < n; i++) {
        int x = StdIn.readInt();
        int y = StdIn.readInt();
        points[i] = new Point2D(x, y);
    }
    FarthestPair farthest = new FarthestPair(points);
    StdOut.println(farthest.distance() + " from " + farthest.either() + " to " + farthest.other());
    return 0;
}