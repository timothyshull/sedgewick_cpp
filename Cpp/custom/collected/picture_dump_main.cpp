#include <jmorecfg.h>
#include "Picture.h"
#include "utility.h"
#include "Binary_std_in.h"

int main(int argc, char* argv[])
{
    int width{utility::str_to_num(argv[1])};
    int height{utility::str_to_num(argv[2])};
    Picture picture{width, height};
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            if (!Binary_std_in::is_empty()) {
                boolean bit = Binary_std_in::read_boolean();
                if (bit) { picture.set(col, row, Color.BLACK); }
                else { picture.set(col, row, Color.WHITE); }
            } else {
                picture.set(col, row, Color.RED);
            }
        }
    }
    picture.show();
    return 0;
}