// line segment
#pragma once

#include "Tri/LineT.h"

#include "Tri/Point3d.h"
#include "Tri/Vector3d.h"

class Line3d : public LineT<Point3d, Vector3d>
{
public:
    using Base = LineT<Point3d, Vector3d>;
    using Base::Base;
};

[[nodiscard]] bool isNear(const Line3d& l1, const Line3d& l2, double tolerance);
