#include "shader.h"

#include "function/global/global_context.h"

#include "core/base/macro.h"
#include "core/file/file_system.h"

namespace Untitled
{
    Shader::Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path)
    {
        std::string vshader_src = g_global_context.m_file_system->readFile(vertex_shader_path);
        std::string fshader_src = g_global_context.m_file_system->readFile(fragment_shader_path);
        auto vshader_id = glCreateShader(GL_VERTEX_SHADER);
        auto fshader_id = glCreateShader(GL_FRAGMENT_SHADER);
        auto vshader_src_ptr = vshader_src.c_str();
        auto fshader_src_ptr = fshader_src.c_str();
        glShaderSource(vshader_id, 1, &vshader_src_ptr, nullptr);
        glShaderSource(fshader_id, 1, &fshader_src_ptr, nullptr);
        glCompileShader(vshader_id);
        glCompileShader(fshader_id);

        int success;
        char info[128];
        glGetShaderiv(vshader_id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vshader_id, 128, nullptr, info);
            LOG_ERROR(info);
            throw;
        }

        glGetShaderiv(fshader_id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fshader_id, 128, nullptr, info);
            LOG_ERROR(info);
            throw;
        }

        m_program = glCreateProgram();
        glAttachShader(m_program, vshader_id);
        glAttachShader(m_program, fshader_id);
        glLinkProgram(m_program);
        glGetProgramiv(m_program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_program, 128, nullptr, info);
            LOG_ERROR(info);
            throw;
        }

        glDeleteShader(vshader_id);
        glDeleteShader(fshader_id);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_program);
    }

    void Shader::activate()
    {
        glUseProgram(m_program);
    }

    void Shader::setUniformMat4(const std::string& uniform_name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_program, uniform_name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::setUniformInt1(const std::string& uniform_name, const GLint& value)
    {
        glUniform1i(glGetUniformLocation(m_program, uniform_name.c_str()), value);
    }

    void Shader::setUniformVec3(const std::string& uniform_name, const glm::vec3& vec)
    {
        glUniform3f(glGetUniformLocation(m_program, uniform_name.c_str()), vec.x, vec.y, vec.z);
    }

    void Shader::setUniformFloat1(const std::string& uniform_name, const GLfloat& value)
    {
        glUniform1f(glGetUniformLocation(m_program, uniform_name.c_str()), value);
    }
}
