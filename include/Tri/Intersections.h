#pragma once
#include "Tri/Line3d.h"

#include <optional>

class Point2d;
class Point3d;
class LineSeg2d;
class LineSeg3d;
class Plane;
struct Triangle;

[[nodiscard]] bool doesIntersect(const Point3d&, const Point3d&);

[[nodiscard]] bool doesIntersect(const Point2d&, const Point2d&);
[[nodiscard]] bool doesIntersect(const Point2d&, const LineSeg2d&);
[[nodiscard]] inline bool doesIntersect(const LineSeg2d& l, const Point2d& p)
{
    return doesIntersect(p, l);
}
[[nodiscard]] bool doesIntersect(const LineSeg2d&, const LineSeg2d&);

[[nodiscard]] bool doesIntersect(const LineSeg3d&, const LineSeg3d&);
[[nodiscard]] bool doesIntersect(const Point3d&, const LineSeg3d&);
[[nodiscard]] inline bool doesIntersect(const LineSeg3d& l, const Point3d& p)
{
    return doesIntersect(p, l);
}

[[nodiscard]] bool doesIntersect(const Point3d&, const Triangle&);
[[nodiscard]] inline bool doesIntersect(const Triangle& t, const Point3d& p)
{
    return doesIntersect(p, t);
}
[[nodiscard]] bool doesIntersect(const LineSeg3d&, const Triangle&);
[[nodiscard]] inline bool doesIntersect(const Triangle& t, const LineSeg3d& l)
{
    return doesIntersect(l, t);
}

std::optional<Line3d> findIntersection(const Plane& plane1, const Plane& plane2);

[[nodiscard]] bool doesIntersect(const Triangle&, const Triangle&);

namespace rawintersect
{

[[nodiscard]] bool doesIntersect(const Point2d&, const LineSeg2d&);
[[nodiscard]] bool doesIntersect(const LineSeg2d&, const LineSeg2d&);
[[nodiscard]] bool doesIntersect(const LineSeg3d&, const LineSeg3d&);
[[nodiscard]] bool doesIntersect(const Point3d&, const LineSeg3d&);
[[nodiscard]] bool doesIntersect(const Point3d&, const Triangle&);
[[nodiscard]] bool doesIntersect(const LineSeg3d&, const Triangle&);
[[nodiscard]] bool doesIntersect(const Triangle&, const Triangle&);

} // namespace rawintersect