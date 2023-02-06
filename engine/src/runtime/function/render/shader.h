#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "core/object/utobject.h"

namespace Untitled
{
    class Shader :public UTObject
    {
    public:
        Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
        ~Shader();

        void activate();
        void setUniformMat4(const std::string& uniform_name, const glm::mat4& matrix);
        void setUniformInt1(const std::string& uniform_name, const GLint& value);
        void setUniformVec3(const std::string& uniform_name, const glm::vec3& vec);
        void setUniformFloat1(const std::string& uniform_name, const GLfloat& value);
    private:
        GLuint m_program;
    };
}
