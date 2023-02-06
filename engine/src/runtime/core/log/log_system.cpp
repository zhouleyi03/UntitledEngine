#include "log_system.h"

namespace Untitled
{
    LogSystem::LogSystem()
    {
        m_start_timepoint = std::chrono::steady_clock::now();
        m_log_fout.open("utengine.log", std::ios::trunc);
    }

    void LogSystem::printSystemTime(std::ostream& target_ostream)
    {
        auto tp_sys_now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(tp_sys_now);
        auto tm_now = std::localtime(&time_t_now);
        target_ostream << "[" << tm_now->tm_hour << ":" << tm_now->tm_min << ":" << tm_now->tm_sec << "] ";
    }

    void LogSystem::printClockTime(std::ostream& target_ostream)
    {
        target_ostream << "[" << std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - m_start_timepoint).count() << "] ";
    }

    void LogSystem::printArg(std::ostream& target_ostream, const std::string& arg)
    {
        target_ostream << arg << std::endl;
    }

    void LogSystem::logInfo(std::ostream& target_ostream, const std::string& arg)
    {
        printSystemTime(target_ostream);
        target_ostream << "[INFO] ";
        printArg(target_ostream, arg);
    }

    void LogSystem::logWarning(std::ostream& target_ostream, const std::string& arg)
    {
        printSystemTime(target_ostream);
        target_ostream << "[WARNING] ";
        printArg(target_ostream, arg);
    }

    void LogSystem::logError(std::ostream& target_ostream, const std::string& arg)
    {
        printSystemTime(target_ostream);
        target_ostream << "[ERROR] ";
        printArg(target_ostream, arg);
    }
}
