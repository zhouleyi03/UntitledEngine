#include "input_system.h"
#include <iostream>
#include "function/global/global_context.h"
#include "function/window/window_system.h"

namespace Untitled
{
    InputSystem::InputSystem()
    {
        auto window_system = g_global_context.m_window_system;
        window_system->registerOnKeyFunc(std::bind(&InputSystem::onKey,
            this,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3,
            std::placeholders::_4));
        window_system->registerOnCursorPosFunc(
            std::bind(&InputSystem::onCursorPos, this, std::placeholders::_1, std::placeholders::_2));
    }

    void InputSystem::tick()
    {
        
    }

    void InputSystem::onKey(int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            switch (key)
            {
            case GLFW_KEY_W:
                m_game_command |= static_cast<unsigned>(GameCommand::forward);
                break;
            case GLFW_KEY_S:
                m_game_command |= static_cast<unsigned>(GameCommand::backward);
                break;
            case GLFW_KEY_A:
                m_game_command |= static_cast<unsigned>(GameCommand::left);
                break;
            case GLFW_KEY_D:
                m_game_command |= static_cast<unsigned>(GameCommand::right);
                break;
            case GLFW_KEY_ESCAPE:
                g_global_context.m_window_system->setWindowShouldClose(true);
                break;
            default:
                break;
            }
        }
        else if (action == GLFW_RELEASE)
        {
            switch (key)
            {
            case GLFW_KEY_W:
                m_game_command &= ~static_cast<unsigned>(GameCommand::forward);
                break;
            case GLFW_KEY_S:
                m_game_command &= ~static_cast<unsigned>(GameCommand::backward);
                break;
            case GLFW_KEY_A:
                m_game_command &= ~static_cast<unsigned>(GameCommand::left);
                break;
            case GLFW_KEY_D:
                m_game_command &= ~static_cast<unsigned>(GameCommand::right);
                break;
            default:
                break;
            }
        }
    }

    void InputSystem::onCursorPos(double current_cursor_x, double current_cursor_y)
    {

    }

    bool InputSystem::checkGameCommandState(GameCommand game_command)
    {
        return static_cast<bool>(m_game_command & static_cast<unsigned>(game_command));
    }

    unsigned int InputSystem::getGameCommand() const
    {
        return m_game_command;
    }
}
