#pragma once
#include <string>

#include "core/meta/reflection/reflection.h"

namespace Untitled
{
    struct WindowCreateInfo
    {
        REFLECTION_START(WindowCreateInfo,
            REFLECTION_FIELD_DEF(int, window_width),
            REFLECTION_FIELD_DEF(int, window_height),
            REFLECTION_FIELD_DEF(std::string, window_title),
            REFLECTION_FIELD_DEF(int, max_fps))

        int window_width;
        int window_height;
        std::string window_title;
        int max_fps;
    };
}