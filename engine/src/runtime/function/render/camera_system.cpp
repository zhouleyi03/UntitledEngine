#include "camera_system.h"

namespace Untitled
{
    void CameraSystem::tick()
    {
        m_player_camera.tick();
    }

    Camera& CameraSystem::getPlayerCamera()
    {
        return m_player_camera;
    }
}
