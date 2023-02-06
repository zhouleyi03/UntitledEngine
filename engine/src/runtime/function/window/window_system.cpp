#include "window_system.h"

#include "core/base/macro.h"

namespace Untitled
{
    WindowSystem::WindowSystem(const WindowCreateInfo& window_create_info)
    {
        LOG_INFO("Initializing window system...");
        m_window_title = window_create_info.window_title;
        m_window_width = window_create_info.window_width;
        m_window_height = window_create_info.window_height;
        m_max_fps = window_create_info.max_fps;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, UNTITLED_OPENGL_VERSION_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, UNTITLED_OPENGL_VERSION_MINOR);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);

        m_window = glfwCreateWindow(window_create_info.window_width, window_create_info.window_height,
            window_create_info.window_title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_window);

        glfwSwapInterval(0); // no vsync

        glfwWindowHint(GLFW_AUTO_ICONIFY, 0);

        glfwSetWindowUserPointer(m_window, this);

        glfwSetKeyCallback(m_window, keyCallback);
        glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
        glfwSetCursorPosCallback(m_window, cursorPosCallback);
        glfwSetScrollCallback(m_window, scrollCallback);
        glfwSetWindowSizeCallback(m_window, windowSizeCallback);
        glfwSetWindowCloseCallback(m_window, windowCloseCallback);
    }

    WindowSystem::~WindowSystem()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    bool WindowSystem::windowShouldClose()
    {
        return static_cast<bool>(glfwWindowShouldClose(m_window));
    }

    void WindowSystem::setTitle(const std::string& title)
    {
        glfwSetWindowTitle(m_window, title.c_str());
    }

    void WindowSystem::setFocusMode(bool focus_mode)
    {
        m_is_focus_mode = focus_mode;
        glfwSetInputMode(m_window, GLFW_CURSOR, m_is_focus_mode ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }

    void WindowSystem::setWindowShouldClose(bool flag)
    {
        glfwSetWindowShouldClose(m_window, flag);
    }

    void WindowSystem::registerOnKeyFunc(const onKeyFunc& func)
    {
        m_onKeyFunc.push_back(func);
    }

    void WindowSystem::registerOnMouseButtonFunc(const onMouseButtonFunc& func)
    {
        m_onMouseButtonFunc.push_back(func);
    }

    void WindowSystem::registerOnCursorPosFunc(const onCursorPosFunc& func)
    {
        m_onCursorPosFunc.push_back(func);
    }

    void WindowSystem::registerOnScrollFunc(const onScrollFunc& func)
    {
        m_onScrollFunc.push_back(func);
    }

    void WindowSystem::registerOnWindowSizeFunc(const onWindowSizeFunc& func)
    {
        m_onWindowSizeFunc.push_back(func);
    }

    void WindowSystem::registerOnWindowCloseFunc(const onWindowCloseFunc& func)
    {
        m_onWindowCloseFunc.push_back(func);
    }

    void WindowSystem::swapBuffersAndPollEvents()
    {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    void WindowSystem::capFps(float delta_time)
    {
        static int call_counter = 0;
        static float extra_delta_time = 0.0f;

        if (m_max_fps == 0) return;

        ++call_counter;
        if (call_counter == 5)
        {
            call_counter = 0;
            if (extra_delta_time > 0)
                std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(extra_delta_time * 1000000.0f)));
        }
        extra_delta_time += 1.0f / m_max_fps - delta_time;
    }

    GLFWwindow* WindowSystem::getWindow()
    {
        return m_window;
    }

    bool WindowSystem::isFocusMode() const
    {
        return m_is_focus_mode;
    }

    void WindowSystem::onKey(int key, int scancode, int action, int mods)
    {
        for (auto& func : m_onKeyFunc)
            func(key, scancode, action, mods);
    }

    void WindowSystem::onMouseButton(int button, int action, int mods)
    {
        for (auto& func : m_onMouseButtonFunc)
            func(button, action, mods);
    }

    void WindowSystem::onCursorPos(double xpos, double ypos)
    {
        for (auto& func : m_onCursorPosFunc)
            func(xpos, ypos);
    }

    void WindowSystem::onScroll(double xoffset, double yoffset)
    {
        for (auto& func : m_onScrollFunc)
            func(xoffset, yoffset);
    }

    void WindowSystem::onWindowSize(int width, int height)
    {
        m_window_width = width;
        m_window_height = height;

        for (auto& func : m_onWindowSizeFunc)
            func(width, height);
    }
}
