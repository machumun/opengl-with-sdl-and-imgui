#pragma once

#include "opengl_shader.hpp"

#include "../../core/components/camera.hpp"
#include "../../core/components/mesh_renderer.hpp"
#include "../../core/components/light.hpp"

#include "../../core/scene/scene_data.hpp"

#include <string>
#include <vector>

namespace hid
{
    struct OpenGLAssetManager;

    struct OpenGLPipeline
    {
        OpenGLPipeline();
        ~OpenGLPipeline();

        void render(const hid::OpenGLAssetManager &assetManager);

        // for batch
        void setup(const std::shared_ptr<hid::SceneData> &sceneData);

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

        std::shared_ptr<hid::SceneData> sceneData;
        // std::shared_ptr<hid::Object> camera;

        hid::Camera *camera;
        std::vector<hid::MeshRenderer *> meshRenderers;
        std::vector<hid::Light *> pointLights;
    };
}