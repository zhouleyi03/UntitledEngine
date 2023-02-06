#pragma once

namespace Untitled
{
    class UUID
    {
    public:
        UUID();
        unsigned getUUID() const;
    private:
        unsigned m_uuid;
    };
}
