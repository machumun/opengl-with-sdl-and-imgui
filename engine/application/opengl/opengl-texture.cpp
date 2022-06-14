#include "opengl-texture.hpp"

#include "../../core/log.hpp"

#include <iostream>

using hid::OpenGLTexture;

namespace
{
    GLuint createTexture(const hid::Bitmap &bitmap)
    {
        static const std::string logTag{"hid::OpenGLApplication::createBitmapTexture"};
        GLuint textureId;
        glGenTextures(1, &textureId);

        hid::log(logTag, "Created Bitmap Texture... " + std::to_string(textureId));
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
        glBindTexture(GL_TEXTURE_2D, 0);

        hid::log(logTag, "Created Bitmap !! " + std::to_string(textureId));

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
    // shader.setInt(uniformName, internal->textureId);
}

GLuint OpenGLTexture::getTextureId() const
{
    return internal->textureId;
};