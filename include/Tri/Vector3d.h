#pragma once

#include "Tri/Vector3dT.h"

#include <utility>

class Point3d;

class Vector3d : public Vector3dT<double>
{
public:
    using Base = Vector3dT<double>;
    using Base::Base;

    Vector3d() = default;
    Vector3d(const Point3d& p1, const Point3d& p2);
    Vector3d(const Base& v);

    void normalize();
    [[nodiscard]] Vector3d normalized() const;

    // this ,first and second will be othogonal to each other
    [[nodiscard]] std::pair<Vector3d, Vector3d> orts() const;
};

[[nodiscard]] Vector3d operator*(double multiplier, const Vector3d& v);
[[nodiscard]] Vector3d operator*(const Vector3d& v, double multiplier);

[[nodiscard]] Vector3d operator/(double multiplier, const Vector3d& v);
[[nodiscard]] Vector3d operator/(const Vector3d& v, double multiplier);

[[nodiscard]] Vector3d operator+(const Vector3d& v1, const Vector3d& v2);
[[nodiscard]] Vector3d operator-(const Vector3d& v1, const Vector3d& v2);

[[nodiscard]] Vector3d cross(const Vector3d& v1, const Vector3d& v2);
[[nodiscard]] double dot(const Vector3d& v1, const Vector3d& v2);

[[nodiscard]] bool isNear(const Vector3d& v1, const Vector3d& v2, double tolerance);