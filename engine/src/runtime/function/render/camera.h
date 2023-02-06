#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Untitled
{
    class Camera
    {
        friend class RenderSystem;
    public:
        void tick();
        void setCameraPos(const glm::vec3& camera_pos);
    private:
        glm::mat4 m_view;
        glm::vec3 m_camera_pos;
    };
}
