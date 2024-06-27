#pragma once
// Base implementation for Vector3d and point in 3D
#include "Tri/Defs.h"
#include "Tri/IsNear.h"

#include <array>
#include <cmath>
#include <cmath>

template <typename Type>
class Vector3dT
{
public:
    using T = Type;
    enum
    {
        Dim = 3
    };
    using Data = std::array<Type, Dim>;

    Vector3dT(const Data& data)
        : x(data[0])
        , y(data[1])
        , z(data[2]){};

    Vector3dT(Type _x = {}, Type _y = {}, Type _z = {})
        : x(_x)
        , y(_y)
        , z(_z){};

    Vector3dT& operator+=(const Vector3dT& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    [[nodiscard]] bool isDegenerate() const { return isNear(lengthSqr(), 0.0, Tolerance); }

    Vector3dT& operator-=(const Vector3dT& v) { return operator+=(-v); }

    Vector3dT& operator*=(T multiplier)
    {
        scale(multiplier);
        return *this;
    }

    Vector3dT& operator/=(T divider) { return operator*=(static_cast<T>(1.0) / divider); }

    Vector3dT& operator-()
    {
        scale(static_cast<T>(-1.0));
        return *this;
    }

    [[nodiscard]] Vector3dT operator-() const
    {
        Vector3dT v = *this;
        return -v;
    }

    [[nodiscard]] Type length() const { return std::sqrt(lengthSqr()); }
    [[nodiscard]] Type lengthSqr() const { return x * x + y * y + z * z; }

    void scale(Type multiplier)
    {
        x *= multiplier;
        y *= multiplier;
        z *= multiplier;
    }

public:
    Type x, y, z;
};

template <typename Type, typename Type2>
[[nodiscard]] Vector3dT<Type> multiply(Type2 multiplier, const Vector3dT<Type>& v)
{
    Vector3dT<Type> v1 = v;
    v1 *= static_cast<Type>(multiplier);
    return v1;
}

template <typename Type>
[[nodiscard]] Vector3dT<Type> add(const Vector3dT<Type>& v1, const Vector3dT<Type>& v2)
{
    return Vector3dT<Type>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template <typename Type, typename Type2>
[[nodiscard]] bool isNearImpl(const Vector3dT<Type>& v1, const Vector3dT<Type>& v2, Type2 tolerance)
{
    return isNear(v1.x, v2.x, tolerance) && isNear(v1.y, v2.y, tolerance) && isNear(v1.z, v2.z, tolerance);
}
