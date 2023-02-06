#include "camera.h"

namespace Untitled
{
    void Camera::tick()
    {
        m_view = glm::mat4(1.0f);
        m_view = glm::translate(m_view, m_camera_pos);
    }

    void Camera::setCameraPos(const glm::vec3& camera_pos)
    {
        m_camera_pos = camera_pos;
    }
}
