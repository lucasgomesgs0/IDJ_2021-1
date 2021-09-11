#ifndef VEC2_H
#define VEC2_H

#include <math.h>

class Vec2
{
private:
public:
    float x, y;
    Vec2();
    Vec2(float x, float y);
    ~Vec2();

    static Vec2 zero;
    static float Distance(Vec2 &a, Vec2 &b);
    static float Angle(Vec2 &a, Vec2 &b);

    float magnitude();
    Vec2 normalized();

    float Angle();
    void Normalize();
    void Rotate(float rad);

    Vec2 operator+(const Vec2 &a);
    Vec2 operator-(const Vec2 &a);
    Vec2 operator*(const float s);
    float operator*(const Vec2 &a);
    Vec2 operator/(const float s);
};

#endif