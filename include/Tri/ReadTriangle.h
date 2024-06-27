#pragma once

#include "Tri/Triangle.h"

#include <iterator>
#include <optional>
#include <string>

// serializatin staff
[[nodiscard]] std::optional<Point3d> readPoint(std::istream_iterator<double>& it);
[[nodiscard]] std::optional<Triangle> readTriangle(const std::string& line);
