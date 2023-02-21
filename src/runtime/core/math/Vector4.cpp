#include "Vector4.h"

#include "core/math/math.h"
#include "core/macro.h"

namespace Untitled
{
    Vector4::Vector4(F32 x, F32 y, F32 z, F32 w) :
        m_x(x), m_y(y), m_z(z), m_w(w)
    {
    }

    Vector4 Untitled::Vector4::operator+(const Vector4& r) const
    {
        return Vector4(m_x + r.m_x, m_y + r.m_y, m_z + r.m_z, m_w + r.m_w);
    }

    Vector4 Untitled::Vector4::operator-(const Vector4& r) const
    {
        return Vector4(m_x - r.m_x, m_y - r.m_y, m_z - r.m_z, m_w - r.m_w);
    }

    Vector4 Untitled::Vector4::operator*(const Vector4& r) const
    {
        return Vector4(m_x * r.m_x, m_y * r.m_y, m_z * r.m_z, m_w * r.m_w);
    }

    Vector4 Vector4::operator*(F32 scalar) const
    {
        return Vector4(scalar * m_x, scalar * m_y, scalar * m_z, scalar * m_w);
    }

    void Untitled::Vector4::operator+=(const Vector4& r)
    {
        m_x += r.m_x;
        m_y += r.m_y;
        m_z += r.m_z;
        m_w += r.m_w;
    }

    void Untitled::Vector4::operator-=(const Vector4& r)
    {
        m_x -= r.m_x;
        m_y -= r.m_y;
        m_z -= r.m_z;
        m_w -= r.m_w;
    }

    void Untitled::Vector4::operator*=(const Vector4& r)
    {
        m_x *= r.m_x;
        m_y *= r.m_y;
        m_z *= r.m_z;
        m_w *= r.m_w;
    }

    void Vector4::operator*=(F32 scalar)
    {
        m_x *= scalar;
        m_y *= scalar;
        m_z *= scalar;
        m_w *= scalar;
    }

    void Vector4::normalize()
    {
        auto len = length();
        UNTITLED_ASSERT(len != 0.0f);
        m_x /= len;
        m_y /= len;
        m_z /= len;
        m_w /= len;
    }

    F32 Untitled::Vector4::length() const
    {
        return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
    }

    F32 Untitled::Vector4::squaredLength() const
    {
        return m_x * m_x + m_y * m_y + m_z * m_z;
    }

    Vector4 operator*(F32 scalar, const Vector4& r)
    {
        return Vector4(scalar * r.m_x, scalar * r.m_y, scalar * r.m_z, scalar * r.m_w);
    }

    F32 Untitled::dot(const Vector4& l, const Vector4& r)
    {
        return l.m_x * r.m_x + l.m_y * r.m_y + l.m_z * r.m_z + l.m_w * r.m_w;
    }

    Vector4 normalize(const Vector4& v)
    {
        auto len = v.length();
        UNTITLED_ASSERT(len != 0.0f);
        return Vector4(v.m_x / len, v.m_y / len, v.m_z / len, v.m_w / len);
    }
}