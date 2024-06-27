#pragma once

#include "Tri/Vector2dT.h"

class Point2d : public Vector2dT<double>
{

public:
    using Base = Vector2dT<double>;
    using Base::Base;

    Point2d(const Base& vector);
};

[[nodiscard]] Point2d operator*(double multiplier, const Point2d& v);
[[nodiscard]] Point2d operator*(const Point2d& v, double multiplier);

[[nodiscard]] double distanceSqr(const Point2d& p1, const Point2d& p2);
[[nodiscard]] double distance(const Point2d& p1, const Point2d& p2);

[[nodiscard]] bool isNear(const Point2d& v1, const Point2d& v2, double tolerance);
