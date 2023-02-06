#include "entity_wrapper.h"

#include "entity.h"

namespace Untitled
{
    EntityWrapper::EntityWrapper(Entity* entity_ptr) :m_entity_ptr(entity_ptr)
    {
    }

    bool EntityWrapper::operator<(const EntityWrapper& right) const
    {
        return m_entity_ptr->m_pos.z > right.m_entity_ptr->m_pos.z;
    }
}
