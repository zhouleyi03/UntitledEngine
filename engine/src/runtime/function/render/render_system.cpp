#include "render_system.h"

#include <glad/glad.h>

#include "core/base/macro.h"
#include "core/object/object_pool.h"

#include "function/global/global_context.h"
#include "function/window/window_system.h"
#include "function/world/world.h"

#include "resource/resource_system.h"

#include "function/render/shader.h"
#include "function/render/texture.h"
#include "function/render/camera_system.h"

namespace Untitled
{
    RenderSystem::RenderSystem()
    {
        LOG_INFO("Initializing render system...");

        gladLoadGL();

        auto gpu_name = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
        LOG_INFO("GPU: " + gpu_name);

        // OpenGL settings
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1.0f, -1.0f);
        glViewport(0, 0, g_global_context.m_window_system->m_window_width, g_global_context.m_window_system->m_window_height);
        glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // init VAO & VBO for default rendering
        GLfloat vertices[] =
        {
           -0.5f,  0.5f,  0.0f,  1.0f,
            0.5f, -0.5f,  1.0f,  0.0f,
           -0.5f, -0.5f,  0.0f,  0.0f,

           -0.5f,  0.5f,  0.0f,  1.0f,
            0.5f,  0.5f,  1.0f,  1.0f,
            0.5f, -0.5f,  1.0f,  0.0f
        };
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(0);

        // init VAO & VBO for post-processing
        GLfloat quad_vertices[] =
        {
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
             1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
             1.0f, -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f,  1.0f, 1.0f
        };
        glGenVertexArrays(1, &m_scr_VAO);
        glGenBuffers(1, &m_scr_VBO);
        glBindVertexArray(m_scr_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_scr_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), &quad_vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        // init second framebuffer for post-processing
        glGenFramebuffers(1, &m_pp_framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_pp_framebuffer);
        glGenTextures(1, &m_texture_color_buffer);
        glBindTexture(GL_TEXTURE_2D, m_texture_color_buffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, g_global_context.m_window_system->m_window_width,
            g_global_context.m_window_system->m_window_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture_color_buffer, 0);
        glGenRenderbuffers(1, &m_rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, g_global_context.m_window_system->m_window_width,
            g_global_context.m_window_system->m_window_height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        m_projection = glm::perspective(glm::radians(45.0f), static_cast<float>(g_global_context.m_window_system->m_window_width) / static_cast<float>(g_global_context.m_window_system->m_window_height), 0.1f, 50.0f);
        g_global_context.m_window_system->registerOnWindowSizeFunc(std::bind(
            &RenderSystem::updateProjectionMatrix, this, std::placeholders::_1, std::placeholders::_2));

        m_object_pool = g_global_context.m_object_pool;
    }

    void RenderSystem::initEX()
    {
        m_pp_shader = g_global_context.m_resource_system->getUID("post_processing_shader");
    }

    void RenderSystem::tick(float delta_time)
    {
        static auto world = g_global_context.m_world;

        //glBindFramebuffer(GL_FRAMEBUFFER, m_pp_framebuffer);
        glClear(GL_COLOR_BUFFER_BIT);

        while (!m_entity_update_queue.empty())
        {
            drawEntity(m_entity_update_queue.top().m_entity_ptr);
            m_entity_update_queue.pop();
        }

        /*
        auto shader = m_object_pool->getObject<Shader>(m_pp_shader);
        shader->activate();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(m_scr_VAO);
        glBindTexture(GL_TEXTURE_2D, m_texture_color_buffer);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        */
    }

    void RenderSystem::drawEntity(Entity* entity)
    {
        auto shader = m_object_pool->getObject<Shader>(entity->m_shader);
        m_object_pool->getObject<Texture>(entity->m_texture)->bindTexture();

        glm::mat4 model(1.0f);
        model = glm::translate(model, entity->m_pos);
        model = glm::scale(model, entity->m_size);
        shader->activate();
        shader->setUniformInt1("entity_sampler", 0);
        shader->setUniformMat4("model", model);
        shader->setUniformMat4("view", g_global_context.m_camera_system->getPlayerCamera().m_view);
        shader->setUniformMat4("projection", m_projection);

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void RenderSystem::registerToUpdateQueue(Entity* entity)
    {
        m_entity_update_queue.push(entity);
    }

    void RenderSystem::updateProjectionMatrix(int width, int height)
    {
        if (width == 0) return; // if lost focus, both width and height will "become" zero
        m_projection = glm::perspective(glm::radians(45.0f), static_cast<float>(g_global_context.m_window_system->m_window_width) / static_cast<float>(g_global_context.m_window_system->m_window_height), 0.1f, 50.0f);
        glViewport(0, 0, width, height);
    }
}
