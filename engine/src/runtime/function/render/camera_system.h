#pragma once
#include "camera.h"

namespace Untitled
{
    class CameraSystem
    {
    public:
        void tick();
        Camera& getPlayerCamera();
    private:
        Camera m_player_camera;
    };
}
