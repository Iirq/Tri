#include "Tri/Matrix3x3.h"

#include "Tri/IsNear.h"

Matrix3x3::Matrix3x3()
    : m_data{} {};

Matrix3x3::Matrix3x3(const Data& d)
    : m_data(d)
{
}

Matrix3x3::Matrix3x3(const Row& r0, const Row& r1, const Row& r2)
{
    memcpy(m_data.data() + 0, r0.data(), sizeof(double) * dim);
    memcpy(m_data.data() + dim, r1.data(), sizeof(double) * dim);
    memcpy(m_data.data() + 2 * dim, r2.data(), sizeof(double) * dim);
}

const Matrix3x3::Row& Matrix3x3::operator[](Indexes i) const
{
    return reinterpret_cast<const Row&>(m_data.data()[i * dim]);
}

std::optional<Vector3d> solveAxb(const Matrix3x3& m, const Vector3d& ib)
{
    Vector3d b = ib;
    using I = Matrix3x3::Indexes;

    // Solve by pivotization.
    double v00 = m[I::i0][0];
    double v10 = m[I::i1][0];
    double v20 = m[I::i2][0];

    double v01 = m[I::i0][1];
    double v11 = m[I::i1][1];
    double v21 = m[I::i2][1];

    double v02 = m[I::i0][2];
    double v12 = m[I::i1][2];
    double v22 = m[I::i2][2];

    double av00 = std::abs(v00);
    double av10 = std::abs(v10);
    double av20 = std::abs(v20);

    // Find which item in first column has largest absolute value.
    if (av10 >= av00 && av10 >= av20)
    {
        std::swap(v00, v10);
        std::swap(v01, v11);
        std::swap(v02, v12);
        std::swap(b.x, b.y);
    }
    else if (av20 >= av00)
    {
        std::swap(v00, v20);
        std::swap(v01, v21);
        std::swap(v02, v22);
        std::swap(b.x, b.y);
    }

    /* a b c | x
       d e f | y
       g h i | z , where |a| >= |d| && |a| >= |g| */

    if (isNear(v00, 0.0, Tolerance)) return {};

    // Scale row so that leading element is one.
    double denom = 1.0 / v00;
    //	v00 = 1.0;
    v01 *= denom;
    v02 *= denom;
    b.x *= denom;

    /* 1 b c | x
       d e f | y
       g h i | z */

    // Zero first column of second and third rows.
    v11 -= v10 * v01;
    v12 -= v10 * v02;
    b.y -= v10 * b.x;

    v21 -= v20 * v01;
    v22 -= v20 * v02;
    b.z -= v20 * b.x;

    /* 1 b c | x
       0 e f | y
       0 h i | z */

    // Pivotize again.
    if (std::abs(v21) > std::abs(v11))
    {
        std::swap(v11, v21);
        std::swap(v12, v22);
        std::swap(b.y, b.z);
    }

    if (isNear(v11, 0.0)) return {};

    /* 1 b c | x
       0 e f | y
       0 h i | z, where |e| >= |h| */

    denom = 1.0 / v11;
    //	v11 = 1.0;
    v12 *= denom;
    b.y *= denom;

    /* 1 b c | x
       0 1 f | y
       0 h i | z */

    v22 -= v21 * v12;
    b.z -= v21 * b.y;

    /* 1 b c | x
       0 1 f | y
       0 0 i | z */

    if (isNear(v22, 0.0)) return {};

    Vector3d x;
    x.z = b.z / v22;
    x.y = b.y - x.z * v12;
    x.x = b.x - x.z * v02 - x.y * v01;

    return x;
}
