#include "Matrix3x3.h"

#include "core/math/Vector3.h"

namespace Untitled
{
    Matrix3x3::Matrix3x3(F32 diag)
    {
        m_data[0][0] = diag;
        m_data[1][1] = diag;
        m_data[2][2] = diag;
    }

    Matrix3x3::Matrix3x3(F32 a11, F32 a12, F32 a13, F32 a21, F32 a22, F32 a23, F32 a31, F32 a32, F32 a33)
    {
        m_data[0][0] = a11;
        m_data[0][1] = a12;
        m_data[0][2] = a13;

        m_data[1][0] = a21;
        m_data[1][1] = a22;
        m_data[1][2] = a23;

        m_data[2][0] = a31;
        m_data[2][1] = a32;
        m_data[2][2] = a33;
    }

    Matrix3x3 Matrix3x3::operator+(const Matrix3x3& r) const
    {
        Matrix3x3 t;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                t.m_data[i][j] = m_data[i][j] + r.m_data[i][j];
        }
        return t;
    }

    Matrix3x3 Matrix3x3::operator-(const Matrix3x3& r) const
    {
        Matrix3x3 t;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                t.m_data[i][j] = m_data[i][j] - r.m_data[i][j];
        }
        return t;
    }

    Matrix3x3 Matrix3x3::operator*(const Matrix3x3& r) const
    {
        Matrix3x3 t;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                    t.m_data[i][j] += m_data[i][k] * r.m_data[k][j];
            }
        }
        return t;
    }

    Matrix3x3 Matrix3x3::operator*(F32 scalar) const
    {
        Matrix3x3 t;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                t.m_data[i][j] = m_data[i][j] * scalar;
        }
        return t;
    }

    void Matrix3x3::operator+=(const Matrix3x3& r)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                m_data[i][j] += r.m_data[i][j];
        }
    }

    void Matrix3x3::operator-=(const Matrix3x3& r)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                m_data[i][j] -= r.m_data[i][j];
        }
    }

    void Matrix3x3::operator*=(const Matrix3x3& r)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                F32 t = 0.0f;
                for (int k = 0; k < 3; k++)
                    t += m_data[i][k] * r.m_data[k][j];
                m_data[i][j] = t;
            }
        }
    }

    void Matrix3x3::operator*=(F32 scalar)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                m_data[i][j] *= scalar;
        }
    }

    void Matrix3x3::transpose()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = i; j < 3; j++)
            {
                F32 t = m_data[j][i];
                m_data[j][i] = m_data[i][j];
                m_data[i][j] = t;
            }
        }
    }

    F32 Matrix3x3::determinant() const
    {
        return m_data[0][0] * (m_data[1][1] * m_data[2][2] - m_data[1][2] * m_data[2][1])
            - m_data[0][1] * (m_data[1][0] * m_data[2][2] - m_data[2][0] * m_data[1][2])
            + m_data[0][2] * (m_data[1][0] * m_data[2][1] - m_data[2][0] * m_data[1][1]);
    }

    Vector3 operator*(const Vector3& v, const Matrix3x3& m)
    {
        return Vector3(v.m_x * m.m_data[0][0] + v.m_y * m.m_data[1][0] + v.m_z * m.m_data[2][0],
            v.m_x * m.m_data[0][1] + v.m_y * m.m_data[1][1] + v.m_z * m.m_data[2][1],
            v.m_x * m.m_data[0][2] + v.m_y * m.m_data[1][2] + v.m_z * m.m_data[2][2]);
    }

    Matrix3x3 transpose(const Matrix3x3& m)
    {
        Matrix3x3 t;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                t.m_data[i][j] = m.m_data[j][i];
        }
        return t;
    }
}
