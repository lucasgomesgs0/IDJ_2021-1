#include "Rect.h"

Rect::Rect() {}

Rect::Rect(float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Rect::~Rect() {}

Rect Rect::zero = Rect(0.0, 0.0, 0.0, 0.0);

float Rect::Distance(Rect &a, Rect &b)
{
    Vec2 v1 = a.Center();
    Vec2 v2 = b.Center();

    return Vec2::Distance(v1, v2);
}

Vec2 Rect::Center()
{
    Vec2 v(x + w / 2, y + h / 2);
    return v;
}

bool Rect::Contains(const Vec2 &a)
{
    if ((a.x >= x) && (a.x <= x + w) && (a.y >= y) && (a.y <= y + h))
    {
        return true;
    }

    return false;
}

Rect Rect::operator+(const Vec2 &a)
{
    return Rect(x + a.x, y + a.y, w, h);
}