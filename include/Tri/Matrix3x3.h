#pragma once

#include "Tri/Vector3d.h"

#include <array>
#include <optional>

class Vector3d;

class Matrix3x3
{
public:
    enum Indexes
    {
        i0,
        i1,
        i2,
        count
    };
    enum
    {
        dim = Indexes::count,
        total = dim * dim
    };

    using Row = std::array<double, dim>;
    using Data = std::array<double, total>;

    Matrix3x3();
    Matrix3x3(const Data& d);

    Matrix3x3(const Row& r0, const Row& r1, const Row& r2);

    [[nodiscard]] const Row& operator[](Indexes i) const;

private:
    Data m_data;
};

[[nodiscard]] std::optional<Vector3d> solveAxb(const Matrix3x3& m, const Vector3d& b);
