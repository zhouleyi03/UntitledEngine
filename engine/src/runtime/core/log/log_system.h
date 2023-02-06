#pragma once
#include <cassert>
#include <chrono>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

namespace Untitled
{
    class LogSystem
    {
    public:
        enum class LogLevel :unsigned char
        {
            INFO,
            WARNING,
            ERROR,
        };

        LogSystem();

        void printSystemTime(std::ostream& target_ostream);
        void printClockTime(std::ostream& target_ostream);
        void printArg(std::ostream& target_ostream,const std::string& arg);

        template <typename Arg0, typename...Args>
        void log(const LogLevel& log_level, Arg0 arg0, Args... args)
        {
            switch (log_level)
            {
            case LogLevel::INFO:
                logInfo(std::cout, arg0);
                logInfo(m_log_fout, arg0);
                (log(log_level, args), ...);
                break;
            case LogLevel::WARNING:
                logWarning(std::cout, arg0);
                logWarning(m_log_fout, arg0);
                (log(log_level, args), ...);
                break;
            case LogLevel::ERROR:
                logError(std::cout, arg0);
                logError(m_log_fout, arg0);
                (log(log_level, args), ...);
                break;
            }
        }
    private:
        void logInfo(std::ostream& target_ostream, const std::string& arg);
        void logWarning(std::ostream& target_ostream, const std::string& arg);
        void logError(std::ostream& target_ostream, const std::string& arg);
    private:
        std::chrono::steady_clock::time_point m_start_timepoint;
        std::ofstream m_log_fout;
    };
}
