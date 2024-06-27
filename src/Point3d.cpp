#include "Tri/Point3d.h"

Point3d::Point3d(const Base& v)
    : Base(v)
{
}

Point3d operator*(double multiplier, const Point3d& v)
{
    return multiply(multiplier, v);
}

Point3d operator*(const Point3d& v, double multiplier)
{
    return multiply(multiplier, v);
}

double distanceSqr(const Point3d& p1, const Point3d& p2)
{
    double dx = p2.x - p1.x;
    dx *= dx;
    double dy = p2.y - p1.y;
    dy *= dy;
    double dz = p2.z - p1.z;
    dz *= dz;

    return dx + dy + dz;
}

double distance(const Point3d& p1, const Point3d& p2)
{
    return std::sqrt(distanceSqr(p1, p2));
}

bool isNear(const Point3d& v1, const Point3d& v2, double tolerance)
{
    return isNearImpl(v1, v2, tolerance);
}
