#pragma once
#define UNTITLED_DEBUG

#define UNTITLED_OPENGL_VERSION_MAJOR 3
#define UNTITLED_OPENGL_VERSION_MINOR 3

#include <thread>
#include <chrono>
#include <string>

#include "core/log/log_system.h"
#include "function/global/global_context.h"

#ifdef UNTITLED_DEBUG

#define LOG_INFO(...) Untitled::g_global_context.m_log_system->log( \
    Untitled::LogSystem::LogLevel::INFO, "[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__)

#define LOG_WARNING(...) Untitled::g_global_context.m_log_system->log( \
    Untitled::LogSystem::LogLevel::WARNING, "[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__)

#define LOG_ERROR(...) Untitled::g_global_context.m_log_system->log( \
    Untitled::LogSystem::LogLevel::ERROR, "[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__)

#else

#define LOG_INFO(...) ;
#define LOG_WARNING(...) ;
#define LOG_ERROR(...) ;

#endif

#define THREAD_SLEEP(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))
