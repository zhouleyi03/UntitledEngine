#include "math.h"

#include "core/math/Vector2.h"
#include "core/math/Vector3.h"
#include "core/math/Matrix3x3.h"
#include "core/math/Matrix4x4.h"

namespace Untitled
{
    F32 absf(F32 val)
    {
        return val >= 0.0f ? val : -val;
    }

    F32 sqrt(F32 val)
    {
        F32 x0 = 1.0f, x1 = val;
        while (absf(x0 - x1) >= sqrt_eps)
        {
            x1 = x0;
            x0 = (x0 + val / x0) / 2.0f;
        }
        return x0;
    }

    Vector2 lerp(const Vector2& v1, const Vector2& v2, F32 v1_weight)
    {
        return v1_weight * v1 + (1.0f - v1_weight) * v2;
    }

    Vector3 lerp(const Vector3& v1, const Vector3& v2, F32 v1_weight)
    {
        return v1_weight * v1 + (1.0f - v1_weight) * v2;
    }
}
