#pragma once
#include <memory>
#include <string>

namespace Untitled
{
    class LogSystem;
    class ResourceSystem;
    class WindowSystem;
    class RenderSystem;
    class FileSystem;
    class InputSystem;
    class CameraSystem;

    class World;
    class ObjectPool;

    class GlobalContext
    {
    public:
        void init(const std::string& config_path);
        void shutdown();
    public:
        std::shared_ptr<LogSystem> m_log_system;
        std::shared_ptr<WindowSystem> m_window_system;
        std::shared_ptr<RenderSystem> m_render_system;
        std::shared_ptr<FileSystem> m_file_system;
        std::shared_ptr<ObjectPool> m_object_pool;
        std::shared_ptr<ResourceSystem> m_resource_system;
        std::shared_ptr<InputSystem> m_input_system;
        std::shared_ptr<World> m_world;
        std::shared_ptr<CameraSystem> m_camera_system;
    };

    extern GlobalContext g_global_context;
}