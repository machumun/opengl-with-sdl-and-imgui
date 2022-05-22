#pragma once

#include "../../core/bitmap.hpp"
#include "../../core/internal-ptr.hpp"

namespace hid
{
    struct OpenGLTexture
    {
        OpenGLTexture(const hid::Bitmap &bitmap);
        void bind() const;

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
}