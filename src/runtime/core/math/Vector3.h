#pragma once
#include "core/type.h"

namespace Untitled
{
    class Vector3;

    Vector3 operator*(F32 scalar, const Vector3& r);

    F32 dot(const Vector3& l, const Vector3& r);
    Vector3 cross(const Vector3& l, const Vector3& r);
    Vector3 normalize(const Vector3& v);

    class Vector3
    {
    public:
        Vector3() = default;
        Vector3(F32 x, F32 y, F32 z);

        Vector3 operator+(const Vector3& r) const;
        Vector3 operator-(const Vector3& r) const;
        Vector3 operator*(const Vector3& r) const;
        Vector3 operator*(F32 scalar) const;

        void operator+=(const Vector3& r);
        void operator-=(const Vector3& r);
        void operator*=(const Vector3& r);
        void operator*=(F32 scalar);

        void normalize();

        F32 length() const;
        F32 squaredLength() const;
    public:
        F32 m_x = 0.0f, m_y = 0.0f, m_z = 0.0f;
    };
}
