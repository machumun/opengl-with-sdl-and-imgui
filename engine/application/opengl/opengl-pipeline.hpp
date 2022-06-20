#pragma once

#include "opengl-shader.hpp"

#include "../../core/internal-ptr.hpp"
#include "../../core/light-settings.hpp"
#include "../../core/gui/gui.hpp"
#include "../../core/perspective-camera.hpp"
#include <string>
#include <vector>

namespace hid
{
    struct OpenGLAssetManager;

    struct OpenGLPipeline
    {
        OpenGLPipeline();
        ~OpenGLPipeline();

        void render(
            const hid::OpenGLAssetManager &assetManager,
            const std::shared_ptr<hid::Gui> &userData,
            const hid::PerspectiveCamera &camera);

    private:
        const hid::OpenGLShader shader;
        const hid::OpenGLShader defferedLightingProgram;
        const hid::OpenGLShader blurProgram;
        const hid::OpenGLShader framebufferProgram;
        const hid::OpenGLShader animationProgram;

        // screen rect mesh vao
        const GLuint framebufferVAO;

        // g buffer
        const GLuint baseFBO;
        const GLuint positionTextureId;
        const GLuint normalTextureId;
        const GLuint albedoTextureId;
        const GLuint depthRenderBufferId;

        // deffered lighting buffer
        const GLuint defferedLightingFBO;
        const GLuint baseTextureId;
        const GLuint bloomTextureId;

        GLuint pingpongFBO[2];
        GLuint pingpongBufferTexture[2];
        GLuint pingpongDepthRenderBufferId[2];

        const int pingpongAmount;

        // animation test
        const int animationFrame[4] = {0, 1, 2, 1};
        const int skipFrame = 8;
        int frameCount = 0;
        int animationCount = 0;
    };
}