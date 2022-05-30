#pragma once

#include "../../core/bitmap.hpp"
#include "../../core/internal-ptr.hpp"
#include "../../core/graphics-wrapper.hpp"

#include "opengl-shader.hpp"

namespace hid
{
    struct OpenGLTexture
    {
        OpenGLTexture(const hid::Bitmap &bitmap);
        void bind() const;
        GLuint getTextureId() const;

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
}