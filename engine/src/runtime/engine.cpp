#include "engine.h"

#include "core/base/macro.h"

#include "function/global/global_context.h"
#include "function/window/window_system.h"
#include "function/render/render_system.h"
#include "function/input/input_system.h"
#include "function/render/camera_system.h"
#include "function/world/world.h"

namespace Untitled
{
    void UntitledEngine::init(const std::string& config_path)
    {
        g_global_context.init(config_path);

        LOG_INFO("Initializing engine...");

        m_window_system = g_global_context.m_window_system;
        m_render_system = g_global_context.m_render_system;
        m_input_system = g_global_context.m_input_system;
        m_world = g_global_context.m_world;
        m_camera_system = g_global_context.m_camera_system;
    }

    void UntitledEngine::run()
    {
        LOG_INFO("Running engine...");

        while (!m_window_system->windowShouldClose())
        {
            calculateDeltaTime();
            tick();
        }
    }

    void UntitledEngine::shutdown()
    {
        LOG_INFO("Shutting down engine...");
        g_global_context.shutdown();
    }

    void UntitledEngine::calculateDeltaTime()
    {
        static auto last_tick_time_point = std::chrono::steady_clock::now();
        static auto tick_time_point = last_tick_time_point;

        tick_time_point = std::chrono::steady_clock::now();
        std::chrono::duration<float> time_span =
            std::chrono::duration_cast<std::chrono::duration<float>>
            (tick_time_point - last_tick_time_point);
        m_delta_time = time_span.count();
        last_tick_time_point = tick_time_point;
    }

    void UntitledEngine::calculateFPS()
    {
        static unsigned int frame_count = 0;
        static float average_duration = 0.0f;

        ++frame_count;

        if (frame_count == 1)
            average_duration = m_delta_time;
        else
            average_duration = average_duration * 0.99f + m_delta_time * 0.01f;

        m_window_system->setTitle(m_window_system->m_window_title + " FPS - " + std::to_string(static_cast<int>(1.0f / average_duration)));
    }

    void UntitledEngine::tick()
    {
        logicTick();
        calculateFPS();
        rendererTick();

        m_window_system->swapBuffersAndPollEvents();
        m_window_system->capFps(m_delta_time);
    }

    void UntitledEngine::logicTick()
    {
        m_input_system->tick();
        m_world->tick(m_delta_time);
        m_camera_system->tick();
    }

    void UntitledEngine::rendererTick()
    {
        m_render_system->tick(m_delta_time);
    }
}
