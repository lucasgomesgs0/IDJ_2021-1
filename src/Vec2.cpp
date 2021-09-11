#include "Vec2.h"

Vec2::Vec2() {}

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vec2::~Vec2() {}

Vec2 Vec2::zero = Vec2(0.0, 0.0);
float Vec2::magnitude() { return sqrt(x * x + y * y); }
Vec2 Vec2::normalized() { return Vec2(x, y) / magnitude(); }

float Vec2::Distance(Vec2 &a, Vec2 &b) { return (a - b).magnitude(); }

void Vec2::Normalize()
{
    Vec2 normalized = this->normalized();

    x = normalized.x;
    y = normalized.y;
}

float Vec2::Angle(Vec2 &a, Vec2 &b)
{
    return acos((a * b) / (a.magnitude() * b.magnitude()));
}

float Vec2::Angle()
{
    return atan(y / x);
}

void Vec2::Rotate(float rad)
{
    // anti-clockwise
    float x = this->x * cos(rad) - this->y * sin(rad);
    float y = this->y * cos(rad) + this->x * sin(rad);

    this->x = x;
    this->y = y;
}

Vec2 Vec2::GetRotated(float rad)
{
    Vec2 v;
	v.x = x;
	v.y = y;
	v.Rotate(rad);
	return v;
}

Vec2 Vec2::operator+(const Vec2 &a)
{
    return Vec2(x + a.x, y + a.y);
}

Vec2 Vec2::operator-(const Vec2 &a)
{
    return Vec2(x - a.x, y - a.y);
}

Vec2 Vec2::operator*(const float s)
{
    return Vec2(s * x, s * y);
}

float Vec2::operator*(const Vec2 &a)
{
    return x * a.x + y * a.y;
}

Vec2 Vec2::operator/(const float s)
{
    return Vec2(x / s, y / s);
}
