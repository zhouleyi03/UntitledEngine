#pragma once
#include "core/type.h"

namespace Untitled
{
    class Vector4;

    Vector4 operator*(F32 scalar, const Vector4& r);

    F32 dot(const Vector4& l, const Vector4& r);
    Vector4 normalize(const Vector4& v);

    class Vector4
    {
    public:
        Vector4() = default;
        Vector4(F32 x, F32 y, F32 z, F32 w);

        Vector4 operator+(const Vector4& r) const;
        Vector4 operator-(const Vector4& r) const;
        Vector4 operator*(const Vector4& r) const;
        Vector4 operator*(F32 scalar) const;

        void operator+=(const Vector4& r);
        void operator-=(const Vector4& r);
        void operator*=(const Vector4& r);
        void operator*=(F32 scalar);

        void normalize();

        F32 length() const;
        F32 squaredLength() const;
    public:
        F32 m_x = 0.0f, m_y = 0.0f, m_z = 0.0f, m_w = 0.0f;
    };
}
