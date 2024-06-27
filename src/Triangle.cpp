#include "Tri/Triangle.h"

Triangle::Triangle(const Data& data)
    : p0(data[0])
    , p1(data[1])
    , p2(data[2])
{
}

Plane Triangle::plane() const
{
    Vector3d normal = cross(Vector3d(p0, p1), Vector3d(p0, p2));
    normal.normalize();

    double d = dot(normal, p1);
    return Plane(normal, d);
}

bool Triangle::isDegenerate() const
{
    return isDegeneratedToLineSeg() || isDegeneratedToPoint();
}

bool Triangle::isDegeneratedToPoint() const
{
    return isNear(p0, p1, Tolerance) && isNear(p1, p2, Tolerance);
}

bool Triangle::isDegeneratedToLineSeg() const
{
    return isNear(p0, p1, Tolerance) || isNear(p1, p2, Tolerance) || isNear(p0, p2, Tolerance);
}

std::optional<LineSeg3d> Triangle::getDegeneratedLineSeg() const
{
    if (isNear(p0, p1, Tolerance))
    {
        return LineSeg3d{p2, p1};
    }
    else if (isNear(p1, p2, Tolerance))
    {
        LineSeg3d{p0, p2};
    }
    else if (isNear(p0, p2, Tolerance))
    {
        LineSeg3d{p0, p1};
    }

    return {};
}

double volume(const Point3d& p, const Triangle& t)
{
    Vector3d e1(t.p0, t.p1);
    Vector3d e2(t.p0, t.p2);

    Vector3d n = cross(e1, e2);
    Vector3d toP(t.p0, p);

    return dot(n, toP);
}

double volume(const Point3d& a, const Point3d& b, const Point3d& c, const Point3d& d)
{
    return volume(a, Triangle({b, c, d}));
}

bool isNear(const Triangle& v1, const Triangle& v2, double tolerance)
{
    return isNearImpl(v1.p0, v2.p0, tolerance) && isNearImpl(v1.p1, v2.p1, tolerance) &&
           isNearImpl(v1.p2, v2.p2, tolerance);
}
