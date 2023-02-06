#pragma once
#include <chrono>
#include <memory>
#include <string>

namespace Untitled
{
    class RenderSystem;
    class InputSystem;
    class WindowSystem;
    class CameraSystem;
    class World;

    class UntitledEngine
    {
    public:
        void init(const std::string& config_path);
        void run();
        void shutdown();

        void calculateDeltaTime();
        void calculateFPS();

        void tick();
        void logicTick();
        void rendererTick();
    private:
        float m_delta_time;

        std::shared_ptr<WindowSystem> m_window_system;
        std::shared_ptr<RenderSystem> m_render_system;
        std::shared_ptr<InputSystem> m_input_system;
        std::shared_ptr<CameraSystem> m_camera_system;
        std::shared_ptr<World> m_world;
    };
}
