#include "Tri/Line3d.h"

[[nodiscard]] bool isNear(const Line3d& l1, const Line3d& l2, double tolerance)
{
    return isNearImpl(l1, l2, tolerance);
}