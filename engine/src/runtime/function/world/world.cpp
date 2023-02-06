#include "world.h"

#include "function/entity/character.h"
#include "resource/resource_system.h"
#include "function/global/global_context.h"
#include "function/entity/env_entity.h"

#include <random>
#include <ctime>

namespace Untitled
{
    World::World()
    {
        auto shader = g_global_context.m_resource_system->getUID("entity_shader");
        auto texture = g_global_context.m_resource_system->getUID("grass");
        auto texturepc = g_global_context.m_resource_system->getUID("entity_x");
        auto pc = new Character(shader, texturepc, 0.0, 0.0, 1.0, true);
        m_scenes.emplace_back();
        m_scenes[0].setCharacter(pc);
        std::mt19937_64 engine; engine.seed(std::time(nullptr));
        std::uniform_real_distribution<double> dist(0.0, 100.0);
        std::uniform_real_distribution<double> distz(-2.0, -1.0);
        for (float i = 0; i < 100; i+=0.99f)
            for (float j = 0; j < 100; j+=0.99f)
            m_scenes[0].addEntity(new EnvEntity(shader, texture, i, j, 0.0, 1.0, 1.0));
    }

    void World::tick(float delta_time)
    {
        m_current_scene_id = m_scenes[m_current_scene_id].tick(delta_time);
    }
}
