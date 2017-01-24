int main(int argc, char *argv[]) {
    int x0 = utility::safe_convert_integer(argv[1]);
    int y0 = utility::safe_convert_integer(argv[2]);
    int n = utility::safe_convert_integer(argv[3]);

    Std_draw::setCanvasSize(800, 800);
    Std_draw::setXscale(0, 100);
    Std_draw::setYscale(0, 100);
    Std_draw::setPenRadius(0.005);
    Std_draw::enableDoubleBuffering();

    std::vector<Point_2d> points = new Point_2d[n];
    for (int i = 0; i < n; ++i) {
        int x = Std_random::uniform(100);
        int y = Std_random::uniform(100);
        points[i] = new Point_2d(x, y);
        points[i].draw();
    }

    // draw p = (x0, x1) in red
    Point_2d p = new Point_2d(x0, y0);
    Std_draw::setPenColor(Std_draw::RED);
    Std_draw::setPenRadius(0.02);
    p.draw();


    // draw line segments from p to each point, one at a time, in polar order
    Std_draw::setPenRadius();
    Std_draw::setPenColor(Std_draw::BLUE);
    Arrays.sort(points, p.polarOrder());
    for (int i = 0; i < n; ++i) {
        p.drawTo(points[i]);
        Std_draw::show();
        Std_draw::pause(100);
    }
    return 0;
}