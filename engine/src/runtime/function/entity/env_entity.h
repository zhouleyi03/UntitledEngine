#pragma once
#include "entity.h"

namespace Untitled
{
    class EnvEntity :public Entity
    {
    public:
        EnvEntity(UID shader, UID texture, float x, float y, float z,
            float width, float height);
        virtual void tick(float delta_time) override;
    };
}
