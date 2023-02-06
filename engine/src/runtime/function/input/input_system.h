#pragma once
#include <functional>

namespace Untitled
{
    enum class GameCommand : unsigned
    {
        forward = 1 << 0,                 // W
        backward = 1 << 1,                 // S
        left = 1 << 2,                 // A
        right = 1 << 3,                 // D
        jump = 1 << 4,                 // SPACE
        invalid = static_cast<unsigned>(1 << 31) // lost focus
    };

    class InputSystem
    {
    public:
        InputSystem();
        void tick();

        void onKey(int key, int scancode, int action, int mods);
        void onCursorPos(double current_cursor_x, double current_cursor_y);
        bool checkGameCommandState(GameCommand game_command);

        unsigned int getGameCommand() const;
    private:
        unsigned int m_game_command = 0;
    };
}
