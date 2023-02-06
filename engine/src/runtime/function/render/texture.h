#pragma once
#include <glad/glad.h>

#include "core/object/utobject.h"

namespace Untitled
{
    class Texture :public UTObject
    {
    public:
        Texture(unsigned char* texture_data, int width, int height);
        ~Texture();
        void bindTexture();
    private:
        GLuint m_texture_id;
    };
}
