#include "Red_black_bst.h"

Red_black_color _not(Red_black_color c)
{
    if (c == Red_black_color::red) {
        return Red_black_color::black;
    }
    return Red_black_color::red;
}
