#include "opengl-texture.hpp"
#include "../../core/graphics-wrapper.hpp"

#include <iostream>

using hid::OpenGLTexture;

namespace
{
    GLuint createTexture(const hid::Bitmap &bitmap)
    {
        GLuint textureId;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            bitmap.getWidth(),
            bitmap.getHeight(),
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            bitmap.getPixelData());
        glGenerateMipmap(GL_TEXTURE_2D);

        return textureId;
    }
}
struct OpenGLTexture::Internal
{
    const GLuint textureId;

    Internal(const hid::Bitmap &bitmap)
        : textureId(::createTexture(bitmap)) {}

    ~Internal()
    {
        glDeleteTextures(1, &textureId);
    }
};

OpenGLTexture::OpenGLTexture(const hid::Bitmap &bitmap)
    : internal(hid::make_internal_ptr<Internal>(bitmap)) {}

void OpenGLTexture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, internal->textureId);
}