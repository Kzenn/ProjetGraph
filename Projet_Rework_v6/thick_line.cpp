#include "thick_line.h"

void thick_line(BITMAP *bmp, int x, int y, int x_, int y_,int thickness, int color)
{
    int dx = x - x_;
    int dy = y - y_;
    int d = sqrtf(dx * dx + dy * dy);
    if (!d)
        return;
    int v[8];
    v[0] = x - thickness * dy / d;
    v[1] = y + thickness * dx / d;
    v[2] = x + thickness * dy / d;
    v[3] = y - thickness * dx / d;
    v[4] = x_ + thickness * dy / d;
    v[5] = y_ - thickness * dx / d;
    v[6] = x_ - thickness * dy / d;
    v[7] = y_ + thickness * dx / d;
    polygon(bmp, 4.9, v, color);
}
