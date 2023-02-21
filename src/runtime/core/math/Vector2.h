#pragma once
#include "core/type.h"

namespace Untitled
{
    class Vector2;
    class Vector3;

    Vector2 operator*(F32 scalar, const Vector2& r);

    F32 dot(const Vector2& l, const Vector2& r);
    Vector3 cross(const Vector2& l, const Vector2& r);
    Vector2 normalize(const Vector2& v);

    class Vector2
    {
    public:
        Vector2() = default;
        Vector2(F32 x, F32 y);

        Vector2 operator+(const Vector2& r) const;
        Vector2 operator-(const Vector2& r) const;
        Vector2 operator*(const Vector2& r) const;
        Vector2 operator*(F32 scalar) const;

        void operator+=(const Vector2& r);
        void operator-=(const Vector2& r);
        void operator*=(const Vector2& r);
        void operator*=(F32 scalar);

        void normalize();

        F32 length() const;
        F32 squaredLength() const;
    public:
        F32 m_x = 0.0f, m_y = 0.0f;
    };
}
