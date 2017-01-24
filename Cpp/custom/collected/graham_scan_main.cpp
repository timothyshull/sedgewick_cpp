int main(int argc, char* argv[])
{
    int n = Std_in::read_int();
    std::vector<Point_2d>
    points = new Point_2d[n];
    for (int i = 0; i < n; ++i) {
        int x = Std_in::read_int();
        int y = Std_in::read_int();
        points[i] = new Point_2d(x, y);
    }
    GrahamScan graham = new GrahamScan(points);
    for (Point_2d p : graham.hull()) {
        Std_out::print_line(p);
    }
    return 0;
}