#include "Tri/Plane.h"

Plane::Plane()
    : m_normal{0, 0, 1}
    , m_d{} {};
Plane::Plane(const Vector3d& normal, double d)
    : m_normal{normal.normalized()}
    , m_d{d} {};

double Plane::signedDistance(const Point3d& toPoint) const
{
    return dot(m_normal, toPoint) - m_d;
}
