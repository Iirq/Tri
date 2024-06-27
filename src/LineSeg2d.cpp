#include "Tri/LineSeg2d.h"

bool isNear(const LineSeg2d& l1, const LineSeg2d& l2, double tolerance)
{
    return isNearImpl(l1, l2, tolerance);
}