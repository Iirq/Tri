
#include "Tri/Vector2d.h"
#include "Tri/Point2d.h"

Vector2d::Vector2d(const Point2d& p1, const Point2d& p2)
    : Base(p2.x - p1.x, p2.y - p1.y)
{
}

Vector2d::Vector2d(const Base& v)
    : Base(v)
{
}

void Vector2d::normalize()
{
    *this /= length();
}

Vector2d Vector2d::normalized() const
{
    Vector2d v(*this);
    v.normalize();
    return v;
}

Vector2d Vector2d::ort() const
{
    return {-y, x};
}

Vector2d operator*(double multiplier, const Vector2d& v)
{
    return multiply(multiplier, v);
}

Vector2d operator*(const Vector2d& v, double multiplier)
{
    return multiply(multiplier, v);
}

Vector2d operator/(double multiplier, const Vector2d& v)
{
    return multiply(1.0 / multiplier, v);
}

Vector2d operator/(const Vector2d& v, double multiplier)
{
    return multiply(1.0 / multiplier, v);
}

Vector2d operator+(const Vector2d& v1, const Vector2d& v2)
{
    return add(v1, v2);
}

Vector2d operator-(const Vector2d& v1, const Vector2d& v2)
{
    return add(v1, -v2);
}

double cross(const Vector2d& v1, const Vector2d& v2)
{
    return (v1.x * v2.y) - (v1.y * v2.x);
}

double dot(const Vector2d& v1, const Vector2d& v2)
{
    return (v1.x * v2.x + v1.y * v2.y);
}

bool isNear(const Vector2d& v1, const Vector2d& v2, double tolerance)
{
    return isNearImpl(v1, v2, tolerance);
}
