#include <vector>
#include "Draw.h"

int main(int argc, char *argv[]) {
    Draw draw1{"Test client 1"};
    draw1.square(.2, .8, .1);
    draw1.filledSquare(.8, .8, .2);
    draw1.circle(.8, .2, .2);
    draw1.setPenColor(Draw.MAGENTA);
    draw1.setPenRadius(.02);
    draw1.arc(.8, .2, .1, 200, 45);

    Draw draw2{"Test client 2"};
    draw2.setCanvasSize(900, 200);
    draw2.setPenRadius();
    draw2.setPenColor(Draw.BLUE);
    std::vector<double> x{.1, .2, .3, .2};
    std::vector<double> y{.2, .3, .2, .1};
    draw2.filledPolygon(x, y);

    draw2.setPenColor(Draw.BLACK);
    draw2.text(0.2, 0.5, "bdfdfdfdlack text");
    draw2.setPenColor(Draw.WHITE);
    draw2.text(0.8, 0.8, "white text");
    return 0;
}