#include "resource_system.h"

#include "function/render/shader.h"
#include "function/render/texture.h"

#include "core/file/file_system.h"
#include "core/meta/serialization/serializer.h"

#include "core/base/macro.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Untitled
{
    ResourceSystem::ResourceSystem(const std::string& config_path)
    {
        auto root = g_global_context.m_file_system->readYAMLFile(config_path);

        Serializer<WindowCreateInfo> window_info_serializer;
        window_info_serializer.deserialize(m_window_info, root);
    }

    void ResourceSystem::loadAssets(const std::string& config_path)
    {
        LOG_INFO("Loading assets...");

        auto root = g_global_context.m_file_system->readYAMLFile(config_path);

        auto asset_path = root["AssetPath"];
        std::string texture_path = asset_path["texture_path"].as<std::string>();
        std::string shader_path = asset_path["shader_path"].as<std::string>();
        std::string music_path = asset_path["music_path"].as<std::string>();
        std::string script_path = asset_path["script_path"].as<std::string>();

        loadTexture(texture_path);
        loadShader(shader_path);
        loadMusic(music_path);
        loadScript(script_path);
    }

    const WindowCreateInfo& ResourceSystem::getWindowCreateInfo() const
    {
        return m_window_info;
    }

    void ResourceSystem::loadShader(const std::string& shader_path)
    {
        std::filesystem::path shader_path_t = shader_path;
        auto root = g_global_context.m_file_system->readYAMLFile(shader_path + "/shader.yml");
        for (const auto& shader_node : root)
        {
            std::filesystem::path vs_path = shader_path_t / shader_node.second["vertex_shader"].as<std::string>();
            std::filesystem::path fs_path = shader_path_t / shader_node.second["fragment_shader"].as<std::string>();
            m_res[shader_node.first.as<std::string>()] =
                g_global_context.m_object_pool->registerObject(
                    new Shader(vs_path.string(), fs_path.string()));

            LOG_INFO("<SHADER> " + shader_node.first.as<std::string>() + " is loaded.");
        }
    }

    void ResourceSystem::loadTexture(const std::string& texture_path)
    {
        auto file_system = g_global_context.m_file_system;
        file_system->foreachFile(texture_path, [&](const std::filesystem::path& file_path)
            {
                unsigned char* data = nullptr;
                int width, height, comp;
                stbi_set_flip_vertically_on_load(true);
                data = stbi_load(file_path.string().c_str(), &width, &height, &comp, 0);
                m_res[file_system->stripExtension(file_path.filename().string())] = 
                    g_global_context.m_object_pool->registerObject(new Texture(data, width, height));
                stbi_image_free(data);

                LOG_INFO("<TEXTURE> " + file_system->stripExtension(file_path.filename().string()) + " is loaded.");
            });
    }

    void ResourceSystem::loadMusic(const std::string& music_path)
    {

    }

    void ResourceSystem::loadScript(const std::string& script_path)
    {

    }

    UID ResourceSystem::getUID(const std::string& name)
    {
        assert(m_res.find(name) != m_res.end());
        return m_res[name];
    }
}
