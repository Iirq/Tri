#include "Tri/ReadTriangle.h"

#include <sstream>

std::optional<Point3d> readPoint(std::istream_iterator<double>& it)
{
    size_t i = 0;
    Point3d::Data data;
    for (auto end = std::istream_iterator<double>(); it != end && i < Point3d::Dim; ++it, ++i)
    {
        data[i] = *it;
    }

    if (i < Point3d::Dim)
    {
        return {};
    }

    return data;
}

std::optional<Triangle> readTriangle(const std::string& line)
{
    Triangle::Data data;

    size_t i = 0;
    std::istringstream str(line);
    for (auto it = std::istream_iterator<double>(str), end = std::istream_iterator<double>();
         it != end && i < Triangle::Dim; ++i)
    {
        if (auto p = readPoint(it); p)
        {
            data[i] = *p;
        }
        else
        {
            return {};
        }
    }

    if (i < Triangle::Dim)
    {
        return {};
    }

    return data;
}
