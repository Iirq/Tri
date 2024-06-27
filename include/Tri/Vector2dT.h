#pragma once
// Base implementation for Vector3d and point in 3D
#include "Tri/Defs.h"
#include "Tri/IsNear.h"

#include <array>
#include <cmath>
#include <cmath>

template <typename Type>
class Vector2dT
{
public:
    using T = Type;
    enum
    {
        Dim = 2
    };
    using Data = std::array<Type, Dim>;

    Vector2dT(const Data& data)
        : x(data[0])
        , y(data[1]){};

    Vector2dT(Type _x = {}, Type _y = {})
        : x(_x)
        , y(_y){};

    Vector2dT& operator+=(const Vector2dT& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    [[nodiscard]] bool isDegenerate() const { return isNear(lengthSqr(), 0.0, Tolerance); }

    Vector2dT& operator-=(const Vector2dT& v) { return operator+=(-v); }

    Vector2dT& operator*=(T multiplier)
    {
        scale(multiplier);
        return *this;
    }

    Vector2dT& operator/=(T divider) { return operator*=(static_cast<T>(1.0) / divider); }

    Vector2dT& operator-()
    {
        scale(static_cast<T>(-1.0));
        return *this;
    }

    [[nodiscard]] Vector2dT operator-() const
    {
        Vector2dT v = *this;
        return -v;
    }

    [[nodiscard]] Type length() const { return std::sqrt(lengthSqr()); }
    [[nodiscard]] Type lengthSqr() const { return x * x + y * y; }

    void scale(Type multiplier)
    {
        x *= multiplier;
        y *= multiplier;
    }

public:
    Type x, y;
};

template <typename Type, typename Type2>
[[nodiscard]] Vector2dT<Type> multiply(Type2 multiplier, const Vector2dT<Type>& v)
{
    Vector2dT<Type> v1 = v;
    v1 *= static_cast<Type>(multiplier);
    return v1;
}

template <typename Type>
[[nodiscard]] Vector2dT<Type> add(const Vector2dT<Type>& v1, const Vector2dT<Type>& v2)
{
    return Vector2dT<Type>(v1.x + v2.x, v1.y + v2.y);
}

template <typename Type, typename Type2>
[[nodiscard]] bool isNearImpl(const Vector2dT<Type>& v1, const Vector2dT<Type>& v2, Type2 tolerance)
{
    return isNear(v1.x, v2.x, tolerance) && isNear(v1.y, v2.y, tolerance);
}
