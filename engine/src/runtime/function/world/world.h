#pragma once
#include <vector>

#include "scene.h"

namespace Untitled
{
    class World
    {
    public:
        World();
        void tick(float delta_time);
    private:
        std::vector<Scene> m_scenes;
        std::size_t m_current_scene_id = 0;
    };
}
