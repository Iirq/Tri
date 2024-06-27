#include "Tri/Intersections.h"
#include "TestEngine.h"

#include "Tri/LineSeg2d.h"
#include "Tri/LineSeg3d.h"
#include "Tri/Point3d.h"
#include "Tri/Triangle.h"

namespace Tests
{

namespace
{

struct TriangleVolume : public TestCaseImpl<TriangleVolume>
{
    bool run() const final
    {
        {
            Point3d point({0, 0, 1});
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            if (isNear(volume(point, triangle), 0.0, Tolerance)) return false;
        }
        {
            Point3d point({0, 0, 0});
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            if (!isNear(volume(point, triangle), 0.0, Tolerance)) return false;
        }
        return true;
    }
};
const TriangleVolume addToTestsTriangleVolume;

struct TriangleDegenerate : public TestCaseImpl<TriangleDegenerate>
{
    bool run() const final
    {
        {
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, 1, 0}, Point3d{-1, 0, 0}});
            if (triangle.isDegenerate()) return false;
            if (triangle.isDegeneratedToLineSeg()) return false;
            if (triangle.isDegeneratedToPoint()) return false;
        }
        {
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, -1, 0}, Point3d{1, -1, 0}});
            if (!triangle.isDegenerate()) return false;
            if (!triangle.isDegeneratedToLineSeg()) return false;
            if (!triangle.isDegeneratedToPoint()) return false;
        }
        {
            Triangle triangle({Point3d{1, -1, 0}, Point3d{1, -1, 0}, Point3d{-1, -0, 0}});
            if (!triangle.isDegenerate()) return false;
            if (!triangle.isDegeneratedToLineSeg()) return false;
            if (triangle.isDegeneratedToPoint()) return false;
        }
        return true;
    }
};
const TriangleDegenerate addToTestsTriangleDegenerate;

} // namespace
} // namespace Tests
