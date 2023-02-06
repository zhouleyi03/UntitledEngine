#pragma once
#include <GLFW/glfw3.h>

#include <string>
#include <chrono>
#include <utility>
#include <vector>
#include <functional>

#include "window_create_info.h"

namespace Untitled
{
    class WindowSystem
    {
        using onKeyFunc = std::function<void(int, int, int, int)>;
        using onCharFunc = std::function<void(unsigned int)>;
        using onMouseButtonFunc = std::function<void(int, int, int)>;
        using onCursorPosFunc = std::function<void(double, double)>;
        using onScrollFunc = std::function<void(double, double)>;
        using onWindowSizeFunc = std::function<void(int, int)>;
        using onWindowCloseFunc = std::function<void()>;
    public:
        explicit WindowSystem(const WindowCreateInfo& window_create_info);
        ~WindowSystem();

        void swapBuffersAndPollEvents();
        void capFps(float delta_time);

        void setTitle(const std::string& title);
        void setFocusMode(bool focus_mode);
        void setWindowShouldClose(bool flag);

        void registerOnKeyFunc(const onKeyFunc& func);
        void registerOnMouseButtonFunc(const onMouseButtonFunc& func);
        void registerOnCursorPosFunc(const onCursorPosFunc& func);
        void registerOnScrollFunc(const onScrollFunc& func);
        void registerOnWindowSizeFunc(const onWindowSizeFunc& func);
        void registerOnWindowCloseFunc(const onWindowCloseFunc& func);

        bool windowShouldClose();
        GLFWwindow* getWindow();
        bool isFocusMode() const;
    public:
        std::string m_window_title;
        int m_window_width;
        int m_window_height;
    private:
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowSystem* app = (WindowSystem*)glfwGetWindowUserPointer(window);
            app->onKey(key, scancode, action, mods);
        }

        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
        {
            WindowSystem* app = (WindowSystem*)glfwGetWindowUserPointer(window);
            app->onMouseButton(button, action, mods);
        }

        static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
        {
            WindowSystem* app = (WindowSystem*)glfwGetWindowUserPointer(window);
            app->onCursorPos(xpos, ypos);
        }

        static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
        {
            WindowSystem* app = (WindowSystem*)glfwGetWindowUserPointer(window);
            app->onScroll(xoffset, yoffset);
        }

        static void windowSizeCallback(GLFWwindow* window, int width, int height)
        {
            WindowSystem* app = (WindowSystem*)glfwGetWindowUserPointer(window);
            app->onWindowSize(width, height);
        }

        static void windowCloseCallback(GLFWwindow* window) { glfwSetWindowShouldClose(window, true); }

        void onKey(int key, int scancode, int action, int mods);
        void onMouseButton(int button, int action, int mods);
        void onCursorPos(double xpos, double ypos);
        void onScroll(double xoffset, double yoffset);
        void onWindowSize(int width, int height);
    private:
        GLFWwindow* m_window;
        int m_max_fps;
        bool m_is_focus_mode = false;

        std::vector<onKeyFunc>         m_onKeyFunc;
        std::vector<onMouseButtonFunc> m_onMouseButtonFunc;
        std::vector<onCursorPosFunc>   m_onCursorPosFunc;
        std::vector<onScrollFunc>      m_onScrollFunc;
        std::vector<onWindowSizeFunc>  m_onWindowSizeFunc;
        std::vector<onWindowCloseFunc> m_onWindowCloseFunc;
    };
}
