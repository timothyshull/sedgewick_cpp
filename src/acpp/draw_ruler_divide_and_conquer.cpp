// Program 5.8 - Divide and conquer to draw a ruler
void draw_ruler(int l, int r, int h)
{
    auto m = (l + r) / 2;
    if (h > 0) {
        draw_ruler(l, m, h - 1);
        mark(m, h);
        draw_ruler(m, r, h - 1);
    }
}