#include "uuid.h"

namespace Untitled
{
    UUID::UUID()
    {
        static unsigned uuid = 0;
        m_uuid = uuid++;
    }

    unsigned UUID::getUUID() const
    {
        return m_uuid;
    }
}
