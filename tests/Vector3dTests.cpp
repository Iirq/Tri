#include "Tri/Vector3d.h"
#include "TestEngine.h"

namespace Tests
{

namespace
{

struct VectorOrts3d : public TestCaseImpl<VectorOrts3d>
{
    // bool doesIntersect(const Point2d&, const LineSeg2d&);
    bool run() const final
    {
        {
            Vector3d normal{0, 0, 1};
            auto [uOrt, vOrt] = normal.orts();

            if (!isNear(uOrt.length(), 1, Tolerance)) return false;
            if (!isNear(vOrt.length(), 1, Tolerance)) return false;
            if (!isNear(dot(vOrt, uOrt), 0, Tolerance)) return false;
            if (!isNear(dot(uOrt, normal), 0, Tolerance)) return false;
        }
        return true;
    }
};
const VectorOrts3d addToTestsVectorOrts3d;

} // namespace
} // namespace Tests