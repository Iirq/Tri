#pragma once

#include "Tri/Vector3dT.h"

class Point3d : public Vector3dT<double>
{

public:
    using Base = Vector3dT<double>;
    using Base::Base;

    Point3d(const Base& vector);
};

[[nodiscard]] Point3d operator*(double multiplier, const Point3d& v);
[[nodiscard]] Point3d operator*(const Point3d& v, double multiplier);

[[nodiscard]] double distanceSqr(const Point3d& p1, const Point3d& p2);
[[nodiscard]] double distance(const Point3d& p1, const Point3d& p2);

[[nodiscard]] bool isNear(const Point3d& v1, const Point3d& v2, double tolerance);
