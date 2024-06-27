#include "Tri/LineSeg3d.h"

bool isNear(const LineSeg3d& l1, const LineSeg3d& l2, double tolerance)
{
    return isNearImpl(l1, l2, tolerance);
}