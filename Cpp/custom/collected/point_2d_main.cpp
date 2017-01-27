#include "Point_2d.h"
#include "Std_random.h"
#include "Std_draw.h"

int main(int argc, char* argv[])
{
    int x0{utility::str_to_num(argv[1])};
    int y0{utility::str_to_num(argv[2])};
    int n{utility::str_to_num(argv[3])};

    Std_draw::set_canvas_size(800, 800);
    Std_draw::set_x_scale(0, 100);
    Std_draw::set_y_scale(0, 100);
    Std_draw::set_pen_radius(0.005);
    Std_draw::enable_double_buffering();

    std::vector<Point_2d> points;
    points.reserve(n);
    int x;
    int y;
    for (int i{0}; i < n; ++i) {
        x = Std_random::uniform(100);
        y = Std_random::uniform(100);
        points[i] = Point_2d{x, y};
        points[i].draw();
    }

    Point_2d p{x0, y0};
    Std_draw::set_pen_color(Std_draw::red);
    Std_draw::set_pen_radius(0.02);
    p.draw();

    Std_draw::set_pen_radius();
    Std_draw::set_pen_color(Std_draw::blue);
    std::sort(points.begin(), points.end(), Point_2d::polarOrder());
    for (int i{0}; i < n; ++i) {
        p.draw_to(points[i]);
        Std_draw::show();
        Std_draw::pause(100);
    }
    return 0;
}