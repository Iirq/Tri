#include "Tri/Intersections.h"
#include "Tri/Defs.h"
#include "Tri/LineSeg2d.h"
#include "Tri/LineSeg3d.h"
#include "Tri/Matrix3x3.h"
#include "Tri/Orts3d.h"
#include "Tri/Plane.h"
#include "Tri/Triangle.h"
#include "Tri/ValueRange.h"
#include "Tri/Vector2d.h"

#include <cassert>
#include <algorithm>
#include <tuple>

namespace
{
constexpr ValueRange r01{0, 1};

std::pair<LineSeg3d, LineSeg3d> findIntersectingEdges(const Triangle& t, double da, double db, double dc)
{
    if (da * db > 0.0)
    {
        return {LineSeg3d(t.p0, t.p2), LineSeg3d(t.p1, t.p2)};
    }
    else if (db * dc > 0.0)
    {
        return {LineSeg3d(t.p0, t.p1), LineSeg3d(t.p0, t.p2)};
    }
    else
    {
        return {LineSeg3d(t.p0, t.p1), LineSeg3d(t.p1, t.p2)};
    }
}

std::tuple<LineSeg2d, LineSeg2d, LineSeg2d> project(const Orts3d& orts, const Triangle& t)
{
    Point2d a1;
    Point2d a2 = orts.pointTo(t.p1);
    Point2d a3 = orts.pointTo(t.p2);

    return {{a1, a2}, {a2, a3}, {a3, a1}};
}
} // namespace

bool doesIntersect(const Point2d& p1, const Point2d& p2)
{
    return isNear(p1, p2, Tolerance);
}

bool doesIntersect(const Point2d& p, const LineSeg2d& l)
{
    if (l.isDegenerate()) return doesIntersect(p, l.p0);
    return rawintersect::doesIntersect(p, l);
}

bool doesIntersect(const LineSeg2d& l1, const LineSeg2d& l2)
{
    if (l1.isDegenerate()) return doesIntersect(l1.p0, l2);
    if (l2.isDegenerate()) return doesIntersect(l2.p0, l1);

    return rawintersect::doesIntersect(l1, l2);
}

bool doesIntersect(const Point3d& p1, const Point3d& p2)
{
    return isNear(p1, p2, Tolerance);
}

bool doesIntersect(const Point3d& p, const LineSeg3d& l)
{
    if (l.isDegenerate()) return doesIntersect(p, l.p0);
    return rawintersect::doesIntersect(p, l);
}
bool doesIntersect(const LineSeg3d& l1, const LineSeg3d& l2)
{
    if (l1.isDegenerate()) return doesIntersect(l1.p0, l2);
    if (l2.isDegenerate()) return doesIntersect(l1, l2.p0);

    return rawintersect::doesIntersect(l1, l2);
}

bool doesIntersect(const Point3d& p, const Triangle& t)
{
    if (t.isDegeneratedToPoint()) return doesIntersect(p, t.p0);
    if (auto ls = t.getDegeneratedLineSeg(); ls) return doesIntersect(p, *ls);
    return rawintersect::doesIntersect(p, t);
}

bool doesIntersect(const LineSeg3d& l, const Triangle& t)
{
    if (l.isDegenerate()) return doesIntersect(l.p0, t);
    if (t.isDegeneratedToPoint()) return doesIntersect(t.p0, t);
    if (auto ls = t.getDegeneratedLineSeg(); ls) return doesIntersect(l, *ls);
    return rawintersect::doesIntersect(l, t);
}
bool doesIntersect(const Triangle& t1, const Triangle& t2)
{
    auto checkDegeneration = [](const Triangle& t1, const Triangle& t2) -> std::optional<bool>
    {
        bool degenerated = false;
        if (t1.isDegeneratedToPoint()) return doesIntersect(t1.p0, t2);
        if (auto ls = t1.getDegeneratedLineSeg(); ls) return doesIntersect(*ls, t2);
        return {};
    };

    if (auto intersection = checkDegeneration(t1, t2); intersection)
    {
        return *intersection;
    }
    if (auto intersection = checkDegeneration(t2, t1); intersection)
    {
        return *intersection;
    }

    return rawintersect::doesIntersect(t1, t2);
}

std::optional<Line3d> findIntersection(const Plane& plane1, const Plane& plane2)
{
    Vector3d lineDir = cross(plane1.normal(), plane2.normal());

    if (lineDir.isDegenerate()) return {};
    lineDir.normalize();

    Matrix3x3 m(
        {plane1.normal().x, plane1.normal().y, plane1.normal().z}, //
        {plane2.normal().x, plane2.normal().y, plane2.normal().z}, //
        {lineDir.x, lineDir.y, lineDir.z});

    auto intersectionPos = solveAxb(m, Point3d(plane1.d(), plane2.d(), 0.0));
    if (!intersectionPos)
    {
        intersectionPos = plane1.normal() * plane1.d();
    }

    return Line3d(*intersectionPos, lineDir);
}

namespace rawintersect
{

bool doesIntersect(const Point2d& p, const LineSeg2d& l)
{
    assert(!l.isDegenerate());
    double xDivider = (l.p1.x - l.p0.x);
    if (isNear(xDivider, 0.0, Tolerance))
        return isNear(p.x, l.p0.x, Tolerance) && ValueRange{l.p0.y, l.p1.y}.isInclude(p.y);
    double yDivider = (l.p1.y - l.p0.y);
    if (isNear(yDivider, 0.0, Tolerance))
        return isNear(p.y, l.p0.y, Tolerance) && ValueRange{l.p0.x, l.p1.x}.isInclude(p.x);

    double a = (p.x - l.p0.x) / xDivider;
    double b = (p.y - l.p0.y) / yDivider;

    if (!isNear(a, b, Tolerance)) return false;

    return r01.isInclude(a);
}

bool doesIntersect(const Point3d& p, const LineSeg3d& l)
{
    assert(!l.isDegenerate());

    const Vector3d toPoint(l.p0, p);
    const Vector3d lDir = l.dir();

    if (!cross(toPoint, lDir).isDegenerate())
    {
        return false;
    }

    double projection = dot(lDir, toPoint);
    if (projection < -Tolerance || projection * projection > l.way().lengthSqr() + SquareTolerance) return false;

    return true;
}

bool doesIntersect(const LineSeg2d& l1, const LineSeg2d& l2)
{
    assert(!l1.isDegenerate());
    assert(!l2.isDegenerate());

    const Vector2d e(l1.p0, l2.p0);
    const Vector2d dir0 = l1.way();
    const Vector2d dir1 = l2.way();
    const double sqrLenE = e.lengthSqr();
    const double sqrLen0 = dir0.lengthSqr();
    const double sqrLen1 = dir1.lengthSqr();

    {
        double s = {};
        double t = {};

        double cross = dot(dir0.ort(), dir1);
        double sqrCross = cross * cross;

        if (sqrCross > Tolerance * sqrLen0 * sqrLen1)
        {
            // The lines are not parallel
            s = dot(e.ort(), dir1) / cross;
            t = dot(e.ort(), dir0) / cross;
            // The intersection point is l1.p0 + s * dir0;
            return r01.isInclude(s) && r01.isInclude(t);
        }
    }
    {
        // The line segments are parallel
        double cross = dot(e.ort(), dir0);
        double sqrCross = cross * cross;

        if (sqrCross > Tolerance * sqrLen0 * sqrLenE)
        {
            // The lines are at a positive distance, no intersection.
            return false;
        }
    }

    // The line segments are along the same line. Do an overlap test.
    double s0 = dot(dir0, e) / sqrLen0;
    double s1 = s0 + dot(dir0, dir1) / sqrLen0;
    double smin = std::min(s0, s1);
    double smax = std::max(s0, s1);

    return r01.isInclude(smin) || r01.isInclude(smax);
}

bool doesIntersect(const LineSeg3d& l1, const LineSeg3d& l2)
{
    assert(!l1.isDegenerate());
    assert(!l2.isDegenerate());

    Vector3d dir1 = l1.dir();
    Vector3d dir2 = l2.dir();

    /*
    Solve the two simultaneous equations
    [ (p1 + t1*v1) - (p2 + t2*v2) ] dot v1 = 0       (1)
    [ (p1 + t1*v1) - (p2 + t2*v2) ] dot v2 = 0       (2)
    from equation (1), get t1 = A * t2 + B and substitute in (2)
    to get t2 = (C - A*B) / (A*A - 1)
    A = v2 . v1
    B = (p2 - p1) . v1
    C = (p2 - p1) . v2
    */

    double A = dot(dir1, dir2);
    if (isNear(std::abs(A), 1.0, Tolerance)) // parallel lines
    {
        // overlapping or parallel lines
        if (rawintersect::doesIntersect(l2.p0, l1) || rawintersect::doesIntersect(l2.p1, l1) ||
            rawintersect::doesIntersect(l1.p0, l2) || rawintersect::doesIntersect(l1.p1, l2))
            return true;
    }
    else // non parallel lines
    {
        Vector3d temp_vect(l1.p0, l2.p0);
        double B = dot(temp_vect, dir1);
        double C = dot(temp_vect, dir2);

        double t2 = (C - A * B) / (A * A - 1.0);
        double t1 = A * t2 + B;

        Point3d nearest1 = l1.p0 + dir1 * t1;
        Point3d nearest2 = l2.p0 + dir2 * t2;

        double dist = distance(nearest1, nearest2);
        if (dist < Tolerance)
        {
            // we have a good intersection
            return rawintersect::doesIntersect(nearest1, l1) && rawintersect::doesIntersect(nearest2, l2);
        }
        else
        {
            // skew lines
            return false;
        }
    }

    return false;
}

bool doesIntersect(const Point3d& p, const Triangle& triangle)
{
    assert(!triangle.isDegenerate());

    const Vector3d e01(triangle.p0, triangle.p1);
    const Vector3d e02(triangle.p0, triangle.p2);

    const Vector3d e012Ort = cross(e01, e02);
    const Vector3d p0p(triangle.p0, p);

    double popOrtLength = dot(e012Ort, p0p);
    if (!isNear(popOrtLength, 0.0, Tolerance))
    {
        return false;
    }

    const Vector3d e12(triangle.p1, triangle.p2);
    const double l01 = e01.length();
    const double l02 = e02.length();
    const double l12 = e12.length();

    Vector3d p1p(triangle.p1, p);
    const double d01p = dot(e01 / l01, p0p / l01);
    const double d02p = dot(e02 / l02, p0p / l02);
    const double d12p = dot(e12 / l12, p1p / l12);
    if (r01.isInclude(d01p) && r01.isInclude(d02p) && r01.isInclude(d12p))
    {
        return true;
    }

    return false;
}

bool doesIntersect(const LineSeg3d& lineSeg, const Triangle& triangle)
{
    assert(!lineSeg.isDegenerate());
    assert(!triangle.isDegenerate());

    // triangle edges
    const Vector3d e1(triangle.p0, triangle.p1);
    const Vector3d e2(triangle.p0, triangle.p2);

    double v_lp0_t = volume(lineSeg.p0, triangle);
    double v_lp1_t = volume(lineSeg.p1, triangle);

    if (isNear(v_lp0_t, 0.0, Tolerance))
        if (rawintersect::doesIntersect(lineSeg.p0, triangle)) return true;
    if (isNear(v_lp1_t, 0.0, Tolerance))
        if (rawintersect::doesIntersect(lineSeg.p1, triangle)) return true;
    if (isNear(v_lp0_t, 0.0, Tolerance) && isNear(v_lp1_t, 0.0, Tolerance))
    {
        Orts3d orts(triangle.p0, e1, e2);

        auto [la1, la2, la3] = project(orts, triangle);

        LineSeg2d l(orts.pointTo(lineSeg.p0), orts.pointTo(lineSeg.p1));

        return rawintersect::doesIntersect(la1, l) || //
               rawintersect::doesIntersect(la2, l) || //
               rawintersect::doesIntersect(la3, l);
    }

    if (isLess0(v_lp0_t, Tolerance) == isLess0(v_lp1_t, Tolerance)) return false;

    const double v_l_t01 = volume(lineSeg.p0, lineSeg.p1, triangle.p0, triangle.p1);
    const double v_l_t12 = volume(lineSeg.p0, lineSeg.p1, triangle.p1, triangle.p2);
    const double v_l_t20 = volume(lineSeg.p0, lineSeg.p1, triangle.p2, triangle.p0);

    bool v_l_t01Less0 = isLess0(v_l_t01, Tolerance);
    return (v_l_t01Less0 == isLess0(v_l_t12, Tolerance) && v_l_t01Less0 == std::signbit(v_l_t20));
}

bool doesIntersect(const Triangle& t1, const Triangle& t2)
{
    assert(!t1.isDegenerate());
    assert(!t2.isDegenerate());

    // Is the triangle t2 completely on one side of the plane of this triangle?
    Plane plane1 = t1.plane();
    Plane plane2 = t2.plane();

    if (cross(plane1.normal(), plane2.normal()).isDegenerate())
    {
        // The two triangles lie in the same plane. Perform the intersection test in 2D.
        double h = dot(plane1.normal(), Vector3d(t1.p0, t2.p0));
        if (!isNear(h, 0.0, Tolerance)) return false;

        if (doesIntersect(t2, t1.p0) || doesIntersect(t1, t2.p0)) return true;

        Orts3d orts(t1.p0, plane1.normal());

        auto [la1, la2, la3] = project(orts, t1);
        auto [lb1, lb2, lb3] = project(orts, t2);

        if (rawintersect::doesIntersect(la1, lb1) || rawintersect::doesIntersect(la1, lb2) ||
            rawintersect::doesIntersect(la1, lb3) || rawintersect::doesIntersect(la2, lb1) ||
            rawintersect::doesIntersect(la2, lb2) || rawintersect::doesIntersect(la2, lb3) ||
            rawintersect::doesIntersect(la3, lb1) || rawintersect::doesIntersect(la3, lb2) ||
            rawintersect::doesIntersect(la3, lb3))
        {
            return true;
        }
        return false;
    }
    else
    {
        auto planeTriangleDistances = [](const Plane& plane, const Triangle& t)
        {
            double tdp0 = plane.signedDistance(t.p0);
            double tdp1 = plane.signedDistance(t.p1);
            double tdp2 = plane.signedDistance(t.p2);

            double tMin = std::min(std::min(tdp0, tdp1), tdp2);
            double tMax = std::max(std::max(tdp0, tdp1), tdp2);
            bool notIntersects = (tMax < -Tolerance || tMin > Tolerance);

            return std::tuple{notIntersects, tdp0, tdp1, tdp2};
        };

        const auto [notIntersects2, t2dp0, t2dp1, t2dp2] = planeTriangleDistances(plane1, t2);
        if (notIntersects2) return false;

        const auto [notIntersects1, t1dp0, t1dp1, t1dp2] = planeTriangleDistances(plane2, t1);
        if (notIntersects1) return false;

        // Find the intersection line of the two planes.
        auto planesIntersectionLine = findIntersection(plane1, plane2);
        if (!planesIntersectionLine) return false;

        // Find the two line segments of both triangles which straddle the intersection line.
        auto [edge1a, edge1b] = findIntersectingEdges(t1, t1dp0, t1dp1, t1dp2);
        auto [edge2a, edge2b] = findIntersectingEdges(t2, t2dp0, t2dp1, t2dp2);

        // Find the projection intervals on the intersection line.

        double t1a0 = planesIntersectionLine->pointTo(edge1a.p0);
        double t1a1 = planesIntersectionLine->pointTo(edge1a.p1);
        double t1b0 = planesIntersectionLine->pointTo(edge1b.p0);
        double t1b1 = planesIntersectionLine->pointTo(edge1b.p1);

        double t2a0 = planesIntersectionLine->pointTo(edge2a.p0);
        double t2a1 = planesIntersectionLine->pointTo(edge2a.p1);
        double t2b0 = planesIntersectionLine->pointTo(edge2b.p0);
        double t2b1 = planesIntersectionLine->pointTo(edge2b.p1);

        ValueRange edge1Range{std::min({t1a0, t1a1, t1b0, t1b1}), std::max({t1a0, t1a1, t1b0, t1b1})};
        ValueRange edge2Range{std::min({t2a0, t2a1, t2b0, t2b1}), std::max({t2a0, t2a1, t2b0, t2b1})};

        return doesIntersect(edge1Range, edge2Range);
    }

    return false;
}

} // namespace rawintersect