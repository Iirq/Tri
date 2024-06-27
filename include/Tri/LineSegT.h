// line segment coomon part for 2d and 3d
#pragma once

#include "Tri/Defs.h"

// finite straight line from point p0 to point p1
template <typename Point, typename Vector>
class LineSegT
{
public:
    LineSegT(const Point& ip0, const Point& ip1)
        : p0(ip0)
        , p1(ip1){};

    [[nodiscard]] bool isDegenerate() const { return isNear(p0, p1, Tolerance); }
    [[nodiscard]] Vector way() const { return Vector{p0, p1}; }
    // let's designate by dir normalized direction
    [[nodiscard]] Vector dir() const
    {
        auto w = way();
        if (!isNear(p0, p1, Tolerance)) return w.normalized();
        return w;
    }

public:
    Point p0;
    Point p1;
};

template <typename Point, typename Vector>
[[nodiscard]] bool isNearImpl(const LineSegT<Point, Vector>& l1, const LineSegT<Point, Vector>& l2, double tolerance)
{
    return isNear(l1.p0, l2.p0, tolerance) && isNear(l1.p1, l2.p1, tolerance);
}