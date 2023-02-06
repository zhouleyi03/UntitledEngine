#pragma once
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>

#include <yaml-cpp/yaml.h>

namespace Untitled
{
    class FileSystem
    {
    public:
        std::string readFile(const std::string& path);
        std::string stripExtension(const std::string& filename);
        YAML::Node readYAMLFile(const std::string& path);
        void foreachFile(const std::string& path, const std::function<void(const std::filesystem::path&)>& func);
    };
}
