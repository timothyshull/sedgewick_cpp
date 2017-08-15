// Program 5.9 - Nonrecursive program to draw a ruler
void draw_ruler(int l, int r, int h)
{
    for (auto t = 1, j{1}; t <= h; j += j, ++t) {
        for (auto i = 0; l + j + i <= r; i += j + j) {
            mark(l + j + i, t);
        }
    }
}