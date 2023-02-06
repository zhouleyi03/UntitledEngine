#include "env_entity.h"

#include "function/global/global_context.h"
#include "function/render/render_system.h"

namespace Untitled
{
    EnvEntity::EnvEntity(UID shader, UID texture, float x, float y, float z,
        float width, float height) :
        Entity(shader, texture, x, y, z, width, height)
    {
    }

    void EnvEntity::tick(float delta_time)
    {
        g_global_context.m_render_system->registerToUpdateQueue(this);
    }
}
