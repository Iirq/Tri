#include "TestEngine.h"

#include "Tri/Orts3d.h"
#include "Tri/IsNear.h"
#include "Tri/Point2d.h"

namespace Tests
{

namespace
{

struct ProjectToOrts3d : public TestCaseImpl<ProjectToOrts3d>
{
    // bool doesIntersect(const Point2d&, const LineSeg2d&);
    bool run() const final
    {
        {
            Orts3d orts(Point3d{}, {0, 0, 1});

            Point2d uv = orts.pointTo(Point3d(3, 4, 5));

            if (!isNear(uv.x, 3., Tolerance)) return false;
            if (!isNear(uv.y, 4., Tolerance)) return false;
        }
        {
            Orts3d orts(Point3d{}, {0, 0, 1});

            Point2d uv(3, 4);
            Point3d pointOn = orts.pointAt(uv);

            if (!isNear(pointOn.x, 3., Tolerance)) return false;
            if (!isNear(pointOn.y, 4., Tolerance)) return false;
            if (!isNear(pointOn.z, 0., Tolerance)) return false;
        }
        return true;
    }
};
const ProjectToOrts3d addToTestsOrts3d;

} // namespace
} // namespace Tests