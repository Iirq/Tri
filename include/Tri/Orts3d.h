#pragma once
#include "Tri/Vector3d.h"
#include "Tri/Point3d.h"

class Point2d;

// System of Coordinate in 3D space
class Orts3d
{
public:
    Point3d origin;
    Vector3d x;
    Vector3d y;
    Vector3d z;

    Orts3d(const Point3d& o, const Vector3d& n);
    // vector z = cross(e1,e2);
    Orts3d(const Point3d& o, const Vector3d& e1, const Vector3d& e2);
    // returns uv on this plane
    [[nodiscard]] Point2d pointTo(const Point3d&) const;
    // returns Point3d by uv
    [[nodiscard]] Point3d pointAt(const Point2d&) const;
    [[nodiscard]] Point3d projection(const Point3d&) const;
};
