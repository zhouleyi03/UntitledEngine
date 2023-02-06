#include "global_context.h"

#include "core/log/log_system.h"
#include "core/file/file_system.h"
#include "core/object/object_pool.h"

#include "function/window/window_system.h"
#include "function/render/render_system.h"
#include "function/render/camera_system.h"
#include "function/input/input_system.h"
#include "function/world/world.h"

#include "resource/resource_system.h"

namespace Untitled
{
    GlobalContext g_global_context;

    void GlobalContext::init(const std::string& config_path)
    {
        // Initialization order is important because they have dependency relations.
        m_log_system = std::make_shared<LogSystem>();
        m_file_system = std::make_shared<FileSystem>();
        m_object_pool = std::make_shared<ObjectPool>();
        m_resource_system = std::make_shared<ResourceSystem>(config_path);  
        m_window_system = std::make_shared<WindowSystem>(m_resource_system->getWindowCreateInfo());
        m_render_system = std::make_shared<RenderSystem>();
        m_input_system = std::make_shared<InputSystem>();
        m_camera_system = std::make_shared<CameraSystem>();

        m_resource_system->loadAssets(config_path);
        m_world = std::make_shared<World>();
        m_render_system->initEX(); // some jobs can only be done with loaded assets.
    }

    void GlobalContext::shutdown()
    {
        m_log_system.reset();
        m_window_system.reset();
        m_render_system.reset();
        m_file_system.reset();
        m_object_pool.reset();
    }
}
