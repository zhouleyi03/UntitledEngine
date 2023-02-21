#pragma once
#include "core/type.h"

namespace Untitled
{
    class Matrix3x3;
    class Vector3;
    
    Vector3 operator*(const Vector3& v, const Matrix3x3& m);

    Matrix3x3 transpose(const Matrix3x3& m);

    class Matrix3x3
    {
    public:
        Matrix3x3() = default;
        explicit Matrix3x3(F32 diag);
        Matrix3x3(F32 a11, F32 a12, F32 a13,
            F32 a21, F32 a22, F32 a23,
            F32 a31, F32 a32, F32 a33);

        Matrix3x3 operator+(const Matrix3x3& r) const;
        Matrix3x3 operator-(const Matrix3x3& r) const;
        Matrix3x3 operator*(const Matrix3x3& r) const;
        Matrix3x3 operator*(F32 scalar) const;

        void operator+=(const Matrix3x3& r);
        void operator-=(const Matrix3x3& r);
        void operator*=(const Matrix3x3& r);
        void operator*=(F32 scalar);

        void transpose();

        F32 determinant() const;
    public:
        F32 m_data[3][3] =
        {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };
    };
}
