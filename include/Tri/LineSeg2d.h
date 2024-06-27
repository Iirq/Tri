// line segment
#pragma once

#include "Tri/LineSegT.h"

#include "Tri/Point2d.h"
#include "Tri/Vector2d.h"

class LineSeg2d : public LineSegT<Point2d, Vector2d>
{
public:
    using Base = LineSegT<Point2d, Vector2d>;
    using Base::Base;
};

[[nodiscard]] bool isNear(const LineSeg2d& l1, const LineSeg2d& l2, double tolerance);
