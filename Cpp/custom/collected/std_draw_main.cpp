#include <vector>
#include "Std_draw.h"

int main(int argc, char *argv[]) {
    Std_draw::square(.2, .8, .1);
    Std_draw::filledSquare(.8, .8, .2);
    Std_draw::circle(.8, .2, .2);

    Std_draw::setPenColor(Std_draw::BOOK_RED);
    Std_draw::setPenRadius(.02);
    Std_draw::arc(.8, .2, .1, 200, 45);

    Std_draw::setPenRadius();
    Std_draw::setPenColor(Std_draw::BOOK_BLUE);
    std::vector<double> x{.1, .2, .3, .2};
    std::vector<double> y{.2, .3, .2, .1};
    Std_draw::filledPolygon(x, y);

    Std_draw::setPenColor(Std_draw::BLACK);
    Std_draw::text(0.2, 0.5, "black text");
    Std_draw::setPenColor(Std_draw::WHITE);
    Std_draw::text(0.8, 0.8, "white text");
    return 0;
}