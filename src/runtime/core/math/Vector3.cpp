#include "Vector3.h"

#include "core/math/math.h"
#include "core/macro.h"

namespace Untitled
{
    Vector3::Vector3(F32 x, F32 y, F32 z) :
        m_x(x), m_y(y), m_z(z)
    {
    }

    Vector3 Untitled::Vector3::operator+(const Vector3& r) const
    {
        return Vector3(m_x + r.m_x, m_y + r.m_y, m_z + r.m_z);
    }

    Vector3 Untitled::Vector3::operator-(const Vector3& r) const
    {
        return Vector3(m_x - r.m_x, m_y - r.m_y, m_z - r.m_z);
    }

    Vector3 Untitled::Vector3::operator*(const Vector3& r) const
    {
        return Vector3(m_x * r.m_x, m_y * r.m_y, m_z * r.m_z);
    }

    Vector3 Vector3::operator*(F32 scalar) const
    {
        return Vector3(scalar * m_x, scalar * m_y, scalar * m_z);
    }

    void Untitled::Vector3::operator+=(const Vector3& r)
    {
        m_x += r.m_x;
        m_y += r.m_y;
        m_z += r.m_z;
    }

    void Untitled::Vector3::operator-=(const Vector3& r)
    {
        m_x -= r.m_x;
        m_y -= r.m_y;
        m_z -= r.m_z;
    }

    void Untitled::Vector3::operator*=(const Vector3& r)
    {
        m_x *= r.m_x;
        m_y *= r.m_y;
        m_z *= r.m_z;
    }

    void Vector3::operator*=(F32 scalar)
    {
        m_x *= scalar;
        m_y *= scalar;
        m_z *= scalar;
    }

    void Vector3::normalize()
    {
        auto len = length();
        UNTITLED_ASSERT(len != 0.0f);
        m_x /= len;
        m_y /= len;
        m_z /= len;
    }

    F32 Untitled::Vector3::length() const
    {
        return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
    }

    F32 Untitled::Vector3::squaredLength() const
    {
        return m_x * m_x + m_y * m_y + m_z * m_z;
    }

    Vector3 operator*(F32 scalar, const Vector3& r)
    {
        return Vector3(scalar * r.m_x, scalar * r.m_y, scalar * r.m_z);
    }

    F32 Untitled::dot(const Vector3& l, const Vector3& r)
    {
        return l.m_x * r.m_x + l.m_y * r.m_y + l.m_z * r.m_z;
    }

    Vector3 Untitled::cross(const Vector3& l, const Vector3& r)
    {
        return Vector3(l.m_y * r.m_z - l.m_z * r.m_y,
            l.m_z * r.m_x - l.m_x * r.m_z, l.m_x * r.m_y - l.m_y * r.m_x);
    }

    Vector3 normalize(const Vector3& v)
    {
        auto len = v.length();
        UNTITLED_ASSERT(len != 0.0f);
        return Vector3(v.m_x / len, v.m_y / len, v.m_z / len);
    }
}
