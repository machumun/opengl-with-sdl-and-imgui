#pragma once

#include "../../core/bitmap.hpp"
#include "../../core/texture.hpp"

#include "../../core/wrapper/graphics_wrapper.hpp"

#include "opengl_shader.hpp"

namespace hid
{
    struct OpenGLTexture : public hid::Texture
    {
        const GLuint textureId;
        OpenGLTexture(const hid::Bitmap &bitmap);
        ~OpenGLTexture();
        void bind() const override;
        GLuint getTextureId() const;
    };
}