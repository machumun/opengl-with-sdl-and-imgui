#pragma once

#include "../../core/bitmap.hpp"
#include "../../core/internal-ptr.hpp"
#include "../../core/graphics-wrapper.hpp"

#include "opengl-shader.hpp"

namespace hid
{
    struct OpenGLTexture
    {
        const GLuint textureId;
        OpenGLTexture(const hid::Bitmap &bitmap);
        ~OpenGLTexture();
        void bind() const;
        GLuint getTextureId() const;
    };
}