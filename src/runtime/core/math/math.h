#pragma once
#include "core/type.h"

namespace Untitled
{
    class Vector2;
    class Vector3;
    class Matrix3x3;
    class Matrix4x4;

    constexpr F32 sqrt_eps = 0.01f;

    F32 absf(F32 val);
    F32 sqrt(F32 val);

    Vector2 lerp(const Vector2& v1, const Vector2& v2, F32 v1_weight);
    Vector3 lerp(const Vector3& v1, const Vector3& v2, F32 v1_weight);
}
