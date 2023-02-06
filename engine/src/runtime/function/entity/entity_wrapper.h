#pragma once

namespace Untitled
{
    class Entity;

    class EntityWrapper
    {
    public:
        EntityWrapper(Entity* entity_ptr);
        bool operator<(const EntityWrapper& right) const;
    public:
        Entity* m_entity_ptr;
    };
}
