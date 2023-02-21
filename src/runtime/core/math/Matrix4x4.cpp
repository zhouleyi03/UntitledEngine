#include "Matrix4x4.h"

#include "core/math/Vector4.h"

#include <immintrin.h>

namespace Untitled
{
    Matrix4x4::Matrix4x4(F32 diag)
    {
        m_data[0][0] = diag;
        m_data[1][1] = diag;
        m_data[2][2] = diag;
        m_data[3][3] = diag;
    }

    Matrix4x4::Matrix4x4(F32 a11, F32 a12, F32 a13, F32 a14, F32 a21, F32 a22, F32 a23, F32 a24, F32 a31, F32 a32, F32 a33, F32 a34, F32 a41, F32 a42, F32 a43, F32 a44)
    {
        m_data[0][0] = a11;
        m_data[0][1] = a12;
        m_data[0][2] = a13;
        m_data[0][3] = a14;

        m_data[1][0] = a21;
        m_data[1][1] = a22;
        m_data[1][2] = a23;
        m_data[1][3] = a24;

        m_data[2][0] = a31;
        m_data[2][1] = a32;
        m_data[2][2] = a33;
        m_data[2][3] = a34;

        m_data[3][0] = a41;
        m_data[3][1] = a42;
        m_data[3][2] = a43;
        m_data[3][3] = a44;
    }

    Matrix4x4 Matrix4x4::operator+(const Matrix4x4& r) const
    {
        Matrix4x4 t;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                t.m_data[i][j] = m_data[i][j] + r.m_data[i][j];
        }
        return t;
    }

    Matrix4x4 Matrix4x4::operator-(const Matrix4x4& r) const
    {
        Matrix4x4 t;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                t.m_data[i][j] = m_data[i][j] - r.m_data[i][j];
        }
        return t;
    }

    Matrix4x4 Matrix4x4::operator*(const Matrix4x4& r) const
    {
        Matrix4x4 t;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                    t.m_data[i][j] += m_data[i][k] * r.m_data[k][j];
            }
        }
        return t;
    }

    Matrix4x4 Matrix4x4::operator*(F32 scalar) const
    {
        Matrix4x4 t;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                t.m_data[i][j] = m_data[i][j] * scalar;
        }
        return t;
    }

    void Matrix4x4::operator+=(const Matrix4x4& r)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                m_data[i][j] += r.m_data[i][j];
        }
    }

    void Matrix4x4::operator-=(const Matrix4x4& r)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                m_data[i][j] -= r.m_data[i][j];
        }
    }

    void Matrix4x4::operator*=(const Matrix4x4& r)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                F32 t = 0.0f;
                for (int k = 0; k < 4; k++)
                    t += m_data[i][k] * r.m_data[k][j];
                m_data[i][j] = t;
            }
        }
    }

    void Matrix4x4::operator*=(F32 scalar)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                m_data[i][j] *= scalar;
        }
    }

    void Matrix4x4::transpose()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = i; j < 4; j++)
            {
                F32 t = m_data[j][i];
                m_data[j][i] = m_data[i][j];
                m_data[i][j] = t;
            }
        }
    }

    F32 Matrix4x4::determinant() const
    {
        return
            m_data[0][0] * (m_data[1][1] * (m_data[2][2] * m_data[3][3] - m_data[2][3] * m_data[3][2])
                - m_data[1][2] * (m_data[2][1] * m_data[3][3] - m_data[3][1] * m_data[2][3])
                + m_data[1][3] * (m_data[2][1] * m_data[3][2] - m_data[2][2] * m_data[3][1]))

            - m_data[0][1] * (m_data[1][0] * (m_data[2][2] * m_data[3][3] - m_data[2][3] * m_data[3][2])
                - m_data[1][2] * (m_data[2][0] * m_data[3][3] - m_data[3][0] * m_data[2][3])
                + m_data[1][3] * (m_data[2][0] * m_data[3][2] - m_data[2][2] * m_data[3][0]))

            + m_data[0][2] * (m_data[1][0] * (m_data[2][1] * m_data[3][3] - m_data[2][3] * m_data[3][1])
                - m_data[1][1] * (m_data[2][0] * m_data[3][3] - m_data[2][3] * m_data[3][0])
                + m_data[1][3] * (m_data[2][0] * m_data[3][1] - m_data[2][1] * m_data[3][0]))

            + m_data[0][3] * (m_data[1][0] * (m_data[2][1] * m_data[3][2] - m_data[2][2] * m_data[3][1])
                - m_data[1][1] * (m_data[2][0] * m_data[3][2] - m_data[2][2] * m_data[3][0])
                + m_data[1][2] * (m_data[2][0] * m_data[3][1] - m_data[2][1] * m_data[3][0]));
    }

    Vector4 operator*(const Vector4& v, const Matrix4x4& m)
    {
        F32 vbuf[4] = { v.m_x,v.m_y,v.m_z,v.m_w };
        __m128* vv = reinterpret_cast<__m128*>(vbuf);
        __m128 x = _mm_shuffle_ps(*vv, *vv, 0);
        __m128 y = _mm_shuffle_ps(*vv, *vv, 0);
        __m128 z = _mm_shuffle_ps(*vv, *vv, 0);
        __m128 w = _mm_shuffle_ps(*vv, *vv, 0);
        return Vector4();
    }

    Matrix4x4 transpose(const Matrix4x4& m)
    {
        Matrix4x4 t;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                t.m_data[i][j] = m.m_data[j][i];
        }
        return t;
    }
}

