#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>

#include "core/object/object_pool.h"

#include "function/global/global_context.h"
#include "function/window/window_create_info.h"

namespace Untitled
{
    using UID = unsigned;

    class ResourceSystem
    {
    public:
        ResourceSystem(const std::string& config_path);
        void loadAssets(const std::string& config_path);
        const WindowCreateInfo& getWindowCreateInfo() const;

        void loadShader(const std::string& shader_path);
        void loadTexture(const std::string& texture_path);
        void loadMusic(const std::string& music_path);
        void loadScript(const std::string& script_path);

        UID getUID(const std::string& name);
    private:
        WindowCreateInfo m_window_info;
        std::unordered_map<std::string, UID> m_res;
    };
}
