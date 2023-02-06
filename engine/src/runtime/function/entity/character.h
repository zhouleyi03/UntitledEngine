#pragma once
#include "function/entity/entity.h"

namespace Untitled
{
    class Character :public Entity
    {
    public:
        Character(UID shader, UID texture, float x, float y, float z, bool moveable);

        virtual void tick(float delta_time) override;
    private:
        const float m_move_speed = 5.0f;
        bool m_moveable;
    };
}
