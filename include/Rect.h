#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect
{
private:
public:
    float x, y, w, h;
    Rect(float x, float y, float w, float h);
    ~Rect();

    static Rect zero;
    static float Distance(Rect &a, Rect &b);

    Vec2 Center();
    bool IsInside(const Vec2 &a);

    Rect operator+(const Vec2 &a);
};

#endif