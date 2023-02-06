#include "file_system.h"

#include "core/base/macro.h"

namespace Untitled
{
    std::string FileSystem::readFile(const std::string& path)
    {
        if (!std::filesystem::exists(path))
        {
            LOG_ERROR("File \"" + path + "\" do not exist!");
            throw;
            return std::string();
        }
        
        std::ifstream fin(path);
        std::stringstream ssm;
        ssm << fin.rdbuf();
        return ssm.str();
    }

    std::string FileSystem::stripExtension(const std::string& filename)
    {
        return filename.substr(0,filename.find('.'));
    }

    YAML::Node FileSystem::readYAMLFile(const std::string& path)
    {
        return YAML::LoadFile(path);
    }

    void FileSystem::foreachFile(const std::string& path, const std::function<void(const std::filesystem::path&)>& func)
    {
        for (const auto& iter : std::filesystem::directory_iterator(path))
        {
            if (std::filesystem::is_regular_file(iter))
                func(iter.path());
        }
    }
}
