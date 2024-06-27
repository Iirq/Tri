#include "TestEngine.h"

#include "Tri/Intersections.h"

#include "Tri/LineSeg2d.h"
#include "Tri/LineSeg3d.h"
#include "Tri/Point3d.h"
#include "Tri/Triangle.h"

namespace Tests
{

namespace
{

struct PointLineSeg2d : public TestCaseImpl<PointLineSeg2d>
{
    // bool doesIntersect(const Point2d&, const LineSeg2d&);
    bool run() const final
    {
        {
            Point2d p(1, 2);
            LineSeg2d l({}, {5, 0});
            if (doesIntersect(p, l)) return false;
        }
        {
            Point2d p(1, 0);
            LineSeg2d l({}, {2, 0});
            if (!doesIntersect(p, l)) return false;
        }
        {
            Point2d p(1, 0);
            LineSeg2d l({2, 0}, {4, 0});
            if (doesIntersect(p, l)) return false;
        }
        {
            Point2d p(1, 1);
            LineSeg2d l({-2, -2}, {2, 2});
            if (!doesIntersect(p, l)) return false;
        }
        {
            Point2d p(1, 0);
            LineSeg2d l({-2, 0}, {-5, 0});
            if (doesIntersect(p, l)) return false;
        }
        return true;
    }
};
const PointLineSeg2d addToTestsPointLineSeg2d;

struct PointPointTests : public TestCaseImpl<PointPointTests>
{
    bool run() const final
    {
        {
            Point3d p1(1, 2, 3);
            Point3d p2(4, 5, 6);
            if (doesIntersect(p1, p2)) return false;
        }
        {
            Point3d p1(1, 2, 3);
            Point3d p2(1, 2, 3);
            if (!doesIntersect(p1, p2)) return false;
        }
        return true;
    }
};
const PointPointTests addToTestsPointPointTests;

struct PointLineSeg3d : public TestCaseImpl<PointLineSeg3d>
{
    // bool doesIntersect(const Point3d&, const LineSeg3d&);
    bool run() const final
    {
        {
            Point3d p(1, 2, 3);
            LineSeg3d l({}, {5, 0, 0});
            if (doesIntersect(p, l)) return false;
        }
        {
            Point3d p(1, 0, 0);
            LineSeg3d l({}, {2, 0, 0});
            if (!doesIntersect(p, l)) return false;
        }
        {
            Point3d p(1, 0, 0);
            LineSeg3d l({2, 0, 0}, {5, 0, 0});
            if (doesIntersect(p, l)) return false;
        }
        {
            Point3d p(1, 0, 0);
            LineSeg3d l({-2, 0, 0}, {-3, 0, 0});
            if (doesIntersect(p, l)) return false;
        }
        {
            Point3d p(0, 0, 0);
            LineSeg3d l({-1, -1, 0}, {1, 1, 0});
            if (!doesIntersect(p, l)) return false;
        }
        {
            Point3d p(0, 0, 0);
            LineSeg3d l({1, -1, 0}, {-1, 1, 0});
            if (!doesIntersect(p, l)) return false;
        }
        return true;
    }
};
const PointLineSeg3d addToTestsPointLineSeg3d;

struct LineSegLineSeg2d : public TestCaseImpl<LineSegLineSeg2d>
{
    // bool doesIntersect(const LineSeg2d&, const LineSeg2d&);
    bool run() const final
    {
        {
            LineSeg2d l1({-1, 0}, {-2, 0});
            LineSeg2d l2({1, 0}, {2, 0});
            if (doesIntersect(l1, l2)) return false;
        }
        {
            LineSeg2d l1({1, 0}, {5, 0});
            LineSeg2d l2({2, 0}, {3, 0});
            if (!doesIntersect(l1, l2)) return false;
        }
        {
            LineSeg2d l1({1, -1}, {-1, 1});
            LineSeg2d l2({-1, -1}, {1, 1});
            if (!doesIntersect(l1, l2)) return false;
        }
        return true;
    }
};
const LineSegLineSeg2d addToTestsLineSegLineSeg2d;

struct LineSegLineSeg3d : public TestCaseImpl<LineSegLineSeg3d>
{
    // bool doesIntersect(const LineSeg3d&, const LineSeg3d&);
    bool run() const final
    {
        {
            LineSeg3d l1({-1, 0, 0}, {-2, 0, 0});
            LineSeg3d l2({1, 0, 0}, {2, 0, 0});
            if (doesIntersect(l1, l2)) return false;
        }
        {
            LineSeg3d l1({1, 0, 0}, {5, 0, 0});
            LineSeg3d l2({2, 0, 0}, {3, 0, 0});
            if (!doesIntersect(l1, l2)) return false;
        }
        {
            LineSeg3d l1({1, -1, 0}, {-1, 1, 0});
            LineSeg3d l2({-1, -1, 0}, {1, 1, 0});
            if (!doesIntersect(l1, l2)) return false;
        }
        return true;
    }
};
const LineSegLineSeg3d addToTestsLineSegLineSeg3d;

struct PointTriangle : public TestCaseImpl<PointTriangle>
{
    // bool doesIntersect(const Point3d&, const Triangle&);
    bool run() const final
    {
        {
            Point3d point{0, 0, 1};
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            if (doesIntersect(point, triangle)) return false;
        }
        {
            Point3d point{0, 0, 0};
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            if (!doesIntersect(point, triangle)) return false;
        }
        {
            Point3d point{1, -1, 0};
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            if (!doesIntersect(point, triangle)) return false;
        }
        {
            Point3d point{1, 1, 0};
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            if (!doesIntersect(point, triangle)) return false;
        }
        {
            Point3d point{-1, 0, 0};
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            if (!doesIntersect(point, triangle)) return false;
        }
        {
            Point3d point{0, 3, 0};
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            if (doesIntersect(point, triangle)) return false;
        }
        {
            Point3d point{3, 0, 0};
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            if (doesIntersect(point, triangle)) return false;
        }
        {
            Point3d point{-3, 0, 0};
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            if (doesIntersect(point, triangle)) return false;
        }
        return true;
    }
};
const PointTriangle addToTestsPointTriangle;

struct LineSegTriangle : public TestCaseImpl<LineSegTriangle>
{
    // bool doesIntersect(const LineSeg3d&, const Triangle&);
    bool run() const final
    {
        {
            LineSeg3d lineSeg{{0, 0, 1}, {3, 0, 1}};
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            if (doesIntersect(lineSeg, triangle)) return false;
        }
        {
            LineSeg3d lineSeg{{-0.5, 0, 0}, {0.5, 0, 0}};
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            if (!doesIntersect(lineSeg, triangle)) return false;
        }
        {
            LineSeg3d lineSeg{{2, -2, 0}, {-1, 1, 0}};
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            if (!doesIntersect(lineSeg, triangle)) return false;
        }
        {
            LineSeg3d lineSeg{{0, 0, -2}, {0, 0, 2}};
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            if (!doesIntersect(lineSeg, triangle)) return false;
        }
        {
            LineSeg3d lineSeg{{2, -2, 0}, {2, 2, 0}};
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            if (doesIntersect(lineSeg, triangle)) return false;
        }
        return true;
    }
};
const LineSegTriangle addToTestsLineSegTriangle;

struct PlanePlaneIntersection : public TestCaseImpl<PlanePlaneIntersection>
{
    bool run() const final
    {
        {
            Plane pl1({0, 1, 0}, 0);
            Plane pl2({0, -1, 0}, 0);
            if (findIntersection(pl1, pl2)) return false;
        }
        {
            Plane pl1({0, 1, 0}, 0);
            Plane pl2({0, 1, 0}, 10);
            if (findIntersection(pl1, pl2)) return false;
        }
        {
            Plane pl1({1, 1, 0}, 0);
            Plane pl2({-1, 1, 0}, 0);
            auto line = findIntersection(pl1, pl2);
            if (!line) return false;
            if (!isNear(*line, Line3d(Point3d{}, Vector3d(0, 0, 1)), Tolerance)) return false;
        }

        return true;
    }
};
const PlanePlaneIntersection addToTestsPlanePlaneIntersection;

struct TriangleTriangle : public TestCaseImpl<TriangleTriangle>
{
    // bool doesIntersect(const Triangle&, const Triangle&);
    bool run() const final
    {
        {
            Triangle t1({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            Triangle t2({Point3d{2, -2, 0}, Point3d{2, 2, 0}, Point3d{-2, 0, 0}});
            if (!doesIntersect(t1, t2)) return false;
        }
        {
            Triangle t1({Point3d{1, -1, 1}, Point3d{1, 1, 1}, Point3d{-1, 0, 1}});
            Triangle t2({Point3d{2, -2, 0}, Point3d{2, 2, 0}, Point3d{-2, 0, 0}});
            if (doesIntersect(t1, t2)) return false;
        }
        {
            Triangle t1({Point3d{1, -1, 1}, Point3d{1, 1, 1}, Point3d{-1, 0, -1}});
            Triangle t2({Point3d{1, -1, -1}, Point3d{1, 1, -1}, Point3d{-2, 0, 1}});
            if (!doesIntersect(t1, t2)) return false;
        }
        {
            Triangle t1({Point3d{0, 0, 0}, Point3d{1, 0, 0}, Point3d{0, 1, 0}});
            Triangle t2({Point3d{0, 0, 0}, Point3d{1, 0, 0}, Point3d{0, 1, 0}});
            if (!doesIntersect(t1, t2)) return false;
        }
        {
            Triangle t1({Point3d{0, 0, 0}, Point3d{10, 0, 0}, Point3d{0, 10, 0}});
            Triangle t2({Point3d{1, 1, 0}, Point3d{1, 1, 0}, Point3d{1, 1, 0}});
            if (!doesIntersect(t1, t2)) return false;
        }
        {
            Triangle t1({Point3d{1, 0, 1}, Point3d{2, 0, 1}, Point3d{1, 1, 1}});
            Triangle t2({Point3d{0, 0, 0}, Point3d{1, 0, 0}, Point3d{0, 1, 0}});
            if (doesIntersect(t1, t2)) return false;
        }
        {
            Triangle t1({Point3d{0, 0, 0}, Point3d{1, 0, 0}, Point3d{0, 1, 0}});
            Triangle t2({Point3d{0, 0, -1}, Point3d{1, 0, 1}, Point3d{0, 1, 1}});
            if (!doesIntersect(t1, t2)) return false;
        }
        {
            Triangle t1({Point3d{0, 0, 0}, Point3d{0, 0, 5}, Point3d{5, 5, 5}});
            Triangle t2({Point3d{5, 0, 0}, Point3d{5, 0, 5}, Point3d{0, 5, 5}});
            if (!doesIntersect(t1, t2)) return false;
        }

        return true;
    }
};
const TriangleTriangle addToTestsTriangleTriangle;

} // namespace
} // namespace Tests
