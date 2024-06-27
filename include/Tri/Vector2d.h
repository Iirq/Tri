#pragma once

#include "Tri/Vector2dT.h"

class Point2d;

class Vector2d : public Vector2dT<double>
{
public:
    using Base = Vector2dT<double>;
    using Base::Base;

    Vector2d() = default;
    Vector2d(const Point2d& p1, const Point2d& p2);
    Vector2d(const Base& v);

    void normalize();
    [[nodiscard]] Vector2d normalized() const;

    [[nodiscard]] Vector2d ort() const;
};

[[nodiscard]] Vector2d operator*(double multiplier, const Vector2d& v);
[[nodiscard]] Vector2d operator*(const Vector2d& v, double multiplier);

[[nodiscard]] Vector2d operator/(double multiplier, const Vector2d& v);
[[nodiscard]] Vector2d operator/(const Vector2d& v, double multiplier);

[[nodiscard]] Vector2d operator+(const Vector2d& v1, const Vector2d& v2);
[[nodiscard]] Vector2d operator-(const Vector2d& v1, const Vector2d& v2);

[[nodiscard]] double cross(const Vector2d& v1, const Vector2d& v2);
[[nodiscard]] double dot(const Vector2d& v1, const Vector2d& v2);

[[nodiscard]] bool isNear(const Vector2d& v1, const Vector2d& v2, double tolerance);