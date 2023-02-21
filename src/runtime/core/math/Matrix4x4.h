#pragma once
#include "core/type.h"

namespace Untitled
{
    class Matrix4x4;
    class Vector4;

    Vector4 operator*(const Vector4& v, const Matrix4x4& m);

    Matrix4x4 transpose(const Matrix4x4& m);

    class Matrix4x4
    {
    public:
        Matrix4x4() = default;
        explicit Matrix4x4(F32 diag);
        Matrix4x4(F32 a11, F32 a12, F32 a13, F32 a14,
            F32 a21, F32 a22, F32 a23, F32 a24,
            F32 a31, F32 a32, F32 a33, F32 a34,
            F32 a41, F32 a42, F32 a43, F32 a44);

        Matrix4x4 operator+(const Matrix4x4& r) const;
        Matrix4x4 operator-(const Matrix4x4& r) const;
        Matrix4x4 operator*(const Matrix4x4& r) const;
        Matrix4x4 operator*(F32 scalar) const;

        void operator+=(const Matrix4x4& r);
        void operator-=(const Matrix4x4& r);
        void operator*=(const Matrix4x4& r);
        void operator*=(F32 scalar);

        void transpose();

        F32 determinant() const;
    public:
        F32 m_data[4][4] =
        {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    };
}
