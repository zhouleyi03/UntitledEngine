#pragma once
#include <glm/glm.hpp>

#include "core/object/utobject.h"

namespace Untitled
{
    class Entity :public UTObject
    {
        friend class RenderSystem;
        friend class EntityWrapper;
        friend class QuadTree;
    public:
        Entity(UID shader, UID texture, float x, float y, float z, float width, float height);
        virtual ~Entity() {}
        virtual void tick(float delta_time) {};
    protected:
        UID m_shader;
        UID m_texture;
        glm::vec3 m_pos;
        glm::vec3 m_size;
    };
}
