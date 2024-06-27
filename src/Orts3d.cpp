#include "Tri/Orts3d.h"

#include "Tri/Point2d.h"

Orts3d::Orts3d(const Point3d& o, const Vector3d& n)
    : origin(o)
    , z(n)
{
    auto [u, v] = z.orts();
    x = u;
    y = v;
}

Orts3d::Orts3d(const Point3d& o, const Vector3d& e1, const Vector3d& e2)
    : Orts3d(o, cross(e1, e2).normalized())
{
}

Point2d Orts3d::pointTo(const Point3d& p3d) const
{
    Vector3d toP(origin, p3d);

    return {dot(x, toP), dot(y, toP)};
}

Point3d Orts3d::pointAt(const Point2d& uv) const
{
    return origin + x * uv.x + y * uv.y;
}

Point3d Orts3d::projection(const Point3d& p3d) const
{
    return pointAt(pointTo(p3d));
}
