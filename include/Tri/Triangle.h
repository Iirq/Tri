#pragma once
#include "Tri/LineSeg3d.h"
#include "Tri/Point3d.h"
#include "Tri/Plane.h"

#include <optional>

// three points in 3D space
struct Triangle
{
    enum
    {
        Dim = 3
    };
    using Data = std::array<Point3d, Dim>;

    Triangle() = default;
    Triangle(const Data& data);

    [[nodiscard]] bool isDegenerate() const;
    [[nodiscard]] bool isDegeneratedToPoint() const;
    [[nodiscard]] bool isDegeneratedToLineSeg() const;

    [[nodiscard]] std::optional<LineSeg3d> getDegeneratedLineSeg() const;

    [[nodiscard]] Plane plane() const;

    Point3d p0;
    Point3d p1;
    Point3d p2;
};

[[nodiscard]] double volume(const Point3d& p, const Triangle& t);
[[nodiscard]] double volume(const Point3d& a, const Point3d& b, const Point3d& c, const Point3d& d);

[[nodiscard]] bool isNear(const Triangle& v1, const Triangle& v2, double tolerance);
