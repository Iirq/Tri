// line segment
#pragma once

#include "Tri/LineSegT.h"

#include "Tri/Point3d.h"
#include "Tri/Vector3d.h"

class LineSeg3d : public LineSegT<Point3d, Vector3d>
{
public:
    using Base = LineSegT<Point3d, Vector3d>;
    using Base::Base;
};
