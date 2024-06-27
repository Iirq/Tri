#pragma once
#include "Tri/Point3d.h"
#include "Tri/Vector3d.h"

// plane surface without uv parametrization
class Plane
{
public:
    Plane();
    Plane(const Vector3d& normal, double d);

    [[nodiscard]] const Vector3d& normal() const { return m_normal; }
    [[nodiscard]] double d() const { return m_d; }
    [[nodiscard]] double signedDistance(const Point3d& toPoint) const;

private:
    Vector3d m_normal; // length of 1
    // The offset of this plane from the origin. [similarOverload: normal]
    double m_d = 0;
};