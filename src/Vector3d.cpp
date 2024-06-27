
#include "Tri/Vector3d.h"
#include "Tri/Point3d.h"

Vector3d::Vector3d(const Point3d& p1, const Point3d& p2)
    : Base(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z)
{
}

Vector3d::Vector3d(const Base& v)
    : Base(v)
{
}

void Vector3d::normalize()
{
    *this /= length();
}

Vector3d Vector3d::normalized() const
{
    Vector3d v(*this);
    v.normalize();
    return v;
}

std::pair<Vector3d, Vector3d> Vector3d::orts() const
{
    double sign = std::copysign(1.0, z);
    const double a = -1.0 / (sign + z);
    const double b = x * y * a;

    return {{1.0 + sign * x * x * a, sign * b, -sign * x}, {b, sign + y * y * a, -y}};
}

Vector3d operator*(double multiplier, const Vector3d& v)
{
    return multiply(multiplier, v);
}

Vector3d operator*(const Vector3d& v, double multiplier)
{
    return multiply(multiplier, v);
}

Vector3d operator/(double multiplier, const Vector3d& v)
{
    return multiply(1.0 / multiplier, v);
}

Vector3d operator/(const Vector3d& v, double multiplier)
{
    return multiply(1.0 / multiplier, v);
}

Vector3d operator+(const Vector3d& v1, const Vector3d& v2)
{
    return add(v1, v2);
}

Vector3d operator-(const Vector3d& v1, const Vector3d& v2)
{
    return add(v1, -v2);
}

Vector3d cross(const Vector3d& v1, const Vector3d& v2)
{
    Vector3d cross;

    cross.x = (v1.y * v2.z) - (v1.z * v2.y);
    cross.y = -((v1.x * v2.z) - (v1.z * v2.x));
    cross.z = (v1.x * v2.y) - (v1.y * v2.x);

    return cross;
}

double dot(const Vector3d& v1, const Vector3d& v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

bool isNear(const Vector3d& v1, const Vector3d& v2, double tolerance)
{
    return isNearImpl(v1, v2, tolerance);
}
