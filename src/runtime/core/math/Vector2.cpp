#include "Vector2.h"
#include "Vector3.h"

#include "core/math/math.h"
#include "core/macro.h"

namespace Untitled
{
    Vector2::Vector2(F32 x, F32 y) :
        m_x(x), m_y(y)
    {
    }

    Vector2 Vector2::operator+(const Vector2& r) const
    {
        return Vector2(m_x + r.m_x, m_y + r.m_y);
    }

    Vector2 Vector2::operator-(const Vector2& r) const
    {
        return Vector2(m_x - r.m_x, m_y - r.m_y);
    }

    Vector2 Vector2::operator*(const Vector2& r) const
    {
        return Vector2(m_x * r.m_x, m_y * r.m_y);
    }

    Vector2 Vector2::operator*(F32 scalar) const
    {
        return Vector2(m_x * scalar, m_y * scalar);
    }

    void Vector2::operator+=(const Vector2& r)
    {
        m_x += r.m_x;
        m_y += r.m_y;
    }

    void Vector2::operator-=(const Vector2& r)
    {
        m_x -= r.m_x;
        m_y -= r.m_y;
    }

    void Vector2::operator*=(const Vector2& r)
    {
        m_x *= r.m_x;
        m_y *= r.m_y;
    }

    void Vector2::operator*=(F32 scalar)
    {
        m_x *= scalar;
        m_y *= scalar;
    }

    void Vector2::normalize()
    {
        auto len = length();
        UNTITLED_ASSERT(len != 0.0f);
        m_x /= len;
        m_y /= len;
    }

    F32 Vector2::length() const
    {
        return sqrt(m_x * m_x + m_y * m_y);
    }

    F32 Vector2::squaredLength() const
    {
        return m_x * m_x + m_y * m_y;
    }

    Vector2 operator*(F32 scalar, const Vector2& r)
    {
        return Vector2(scalar * r.m_x, scalar * r.m_y);
    }

    F32 dot(const Vector2& l, const Vector2& r)
    {
        return l.m_x * r.m_x + l.m_y * r.m_y;
    }

    Vector3 cross(const Vector2& l, const Vector2& r)
    {
        return Vector3(0.0f, 0.0f, l.m_x * r.m_y - r.m_x * l.m_y);
    }

    Vector2 normalize(const Vector2& v)
    {
        auto len = v.length();
        UNTITLED_ASSERT(len != 0.0f);
        return Vector2(v.m_x / len, v.m_y / len);
    }
}
