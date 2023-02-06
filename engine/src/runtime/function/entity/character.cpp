#include "character.h"

#include "function/global/global_context.h"
#include "function/input/input_system.h"
#include "function/render/render_system.h"
#include "function/render/camera_system.h"
#include "function/window/window_system.h"

namespace Untitled
{
    Character::Character(UID shader, UID texture, float x, float y, float z, bool moveable) :
        Entity(shader, texture, x, y, z, 1.0f, 1.0f), m_moveable(moveable)
    {
    }

    void Character::tick(float delta_time)
    {
        g_global_context.m_render_system->registerToUpdateQueue(this);
        if (!m_moveable) return;
        float delta_distance = delta_time * m_move_speed;
        int direction = 0;
        int direction_distribution_x = 0;
        int direction_distribution_y = 0;
        if (g_global_context.m_input_system->checkGameCommandState(GameCommand::forward))
            direction |= 1, ++direction_distribution_y;
        if (g_global_context.m_input_system->checkGameCommandState(GameCommand::backward))
            direction |= 2, --direction_distribution_y;
        if (g_global_context.m_input_system->checkGameCommandState(GameCommand::left))
            direction |= 4, --direction_distribution_x;
        if (g_global_context.m_input_system->checkGameCommandState(GameCommand::right))
            direction |= 8, ++direction_distribution_x;
        float distance_factor = std::sqrtf(direction_distribution_x * direction_distribution_x
            + direction_distribution_y * direction_distribution_y);
        if (distance_factor != 0.0f)
            delta_distance /= distance_factor;
        if (direction & 1)
            m_pos.y += delta_distance;
        if (direction & 2)
            m_pos.y -= delta_distance;
        if (direction & 4)
            m_pos.x -= delta_distance;
        if (direction & 8)
            m_pos.x += delta_distance;
        glm::vec3 player_camera_pos(-m_pos.x, -m_pos.y, -4.0f);
        g_global_context.m_camera_system->getPlayerCamera().setCameraPos(player_camera_pos);
    }
}
