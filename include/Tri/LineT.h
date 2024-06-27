// line segment coomon part for 2d and 3d
#pragma once

#include "Tri/Defs.h"

// infinite straight line
template <typename Point, typename Vector>
class LineT
{
public:
    LineT(const Point& p, const Vector& d)
        : m_p(p)
        , m_dir(d)
    {
        if (!m_dir.isDegenerate()) m_dir.normalize();
    }

    [[nodiscard]] bool isDegenerate() const { return m_dir.isDegenerate(); }
    [[nodiscard]] const Point& point() const { return m_p; }
    // let's designate by dir normalized direction
    [[nodiscard]] const Vector& dir() const { return m_dir; }

    // parametric curve staff
    // returns distance to projection of p on this line
    [[nodiscard]] double pointTo(const Point& p) const
    {
        Vector toP(m_p, p);
        return dot(m_dir, toP);
    }
    // returns Point by t
    [[nodiscard]] Point pointAt(double t) const { return m_p + m_dir * t; }
    [[nodiscard]] Point projection(const Point& p) const { return pointAt(pointTo(p)); }

private:
    Point m_p;    // start point
    Vector m_dir; // length of 1
};

template <typename Point, typename Vector>
[[nodiscard]] bool isNearImpl(const LineT<Point, Vector>& l1, const LineT<Point, Vector>& l2, double tolerance)
{
    return isNear(l1.point(), l2.point(), tolerance) && isNear(l1.dir(), l2.dir(), tolerance);
}