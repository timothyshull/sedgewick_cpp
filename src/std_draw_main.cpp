#include <vector>
#include "Std_draw.h"

int main(int argc, char *argv[]) {
    Std_draw::init(argc, argv);
    Std_draw::setup_widgets();
    Std_draw::setup_labels();
    Std_draw::set_layout();
    Std_draw::set_timers();
    return Std_draw::exec();
//    Std_draw::square(.2, .8, .1);
//    Std_draw::filled_square(.8, .8, .2);
//    Std_draw::circle(.8, .2, .2);
//
//    Std_draw::set_pen_color(Std_draw::book_red);
//    Std_draw::set_pen_radius(.02);
//    Std_draw::arc(.8, .2, .1, 200, 45);
//
//    Std_draw::set_pen_radius();
//    Std_draw::set_pen_color(Std_draw::book_blue);
//    std::vector<double> x{.1, .2, .3, .2};
//    std::vector<double> y{.2, .3, .2, .1};
//    Std_draw::filled_polygon(x, y);
//
//    Std_draw::set_pen_color(Std_draw::black);
//    Std_draw::text(0.2, 0.5, "black text");
//    Std_draw::set_pen_color(Std_draw::white);
//    Std_draw::text(0.8, 0.8, "white text");
//    return 0;
}