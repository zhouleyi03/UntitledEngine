#include "entity.h"

namespace Untitled
{
    Entity::Entity(UID shader, UID texture, float x, float y, float z, float width, float height) :
        m_shader(shader), m_texture(texture), m_pos(x, y, z), m_size(width, height, 0.0f)
    {
    }
}
