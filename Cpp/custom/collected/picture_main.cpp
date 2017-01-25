#include "Picture.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    Picture picture{argv[1]};
    Std_out::printf("%d-by-%d\n", picture.width(), picture.height());
    picture.show();
    return 0;
}