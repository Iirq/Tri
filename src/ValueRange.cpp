#include "Tri/ValueRange.h"

#include "Tri/IsNear.h"

bool doesIntersect(const ValueRange& r1, const ValueRange& r2)
{
    return r1.isInclude(r2.start) || r1.isInclude(r2.end);
}

bool isNear(const ValueRange& r1, const ValueRange& r2, double epsilon)
{
    return isNear(r1.start, r2.start, epsilon) && isNear(r1.end, r2.end, epsilon);
}
