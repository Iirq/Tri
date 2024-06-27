#pragma once

#include <limits>

// https://www.codeproject.com/Tips/5288060/Value-Ranges-or-Diapasons
struct ValueRange
{
    double start = (std::numeric_limits<double>::max)();
    double end = -(std::numeric_limits<double>::max)();

    [[nodiscard]] double length() const { return end - start; }
    [[nodiscard]] bool isDegenerate() const { return end < start; }
    [[nodiscard]] bool isInclude(const double u) const { return u >= start && u <= end; }
};

[[nodiscard]] bool doesIntersect(const ValueRange& r1, const ValueRange& r2);
[[nodiscard]] bool isNear(const ValueRange& r1, const ValueRange& r2, double epsilon);
