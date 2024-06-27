#include "Tri/Point2d.h"

Point2d::Point2d(const Base& v)
    : Base(v)
{
}

Point2d operator*(double multiplier, const Point2d& v)
{
    return multiply(multiplier, v);
}

Point2d operator*(const Point2d& v, double multiplier)
{
    return multiply(multiplier, v);
}

double distanceSqr(const Point2d& p1, const Point2d& p2)
{
    double dx = p2.x - p1.x;
    dx *= dx;
    double dy = p2.y - p1.y;
    dy *= dy;

    return dx + dy;
}

double distance(const Point2d& p1, const Point2d& p2)
{
    return std::sqrt(distanceSqr(p1, p2));
}

bool isNear(const Point2d& v1, const Point2d& v2, double tolerance)
{
    return isNearImpl(v1, v2, tolerance);
}
