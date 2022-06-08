#include "opengl-pipeline.hpp"
#include "opengl-asset-manager.hpp"
#include "opengl-shader.hpp"

#include "../../core/assets.hpp"
#include "../../core/graphics-wrapper.hpp"
#include "../../core/log.hpp"

#include <stdexcept>
#include <vector>

// debug
// #include <typeinfo>
// #include <iostream>

using hid::OpenGLPipeline;

namespace
{
    uint32_t viewportWidth = hid::sdl::getDisplaySize().first;
    uint32_t viewportHeight = hid::sdl::getDisplaySize().second;

    GLuint createFramebufferTexture(const GLuint &fbo,
                                    const GLuint &internalFormat,
                                    const GLuint &attachment)
    {

        static const std::string logTag{"hid::OpenGLApplication::createFramebufferTexture"};
        GLuint textureId;
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     internalFormat,
                     viewportWidth,
                     viewportHeight,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, textureId, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        hid::log(logTag, "Created Framebuffer Texture Id: " + std::to_string(textureId) + " Size:" + std::to_string(viewportWidth) + " x " + std::to_string(viewportHeight));

        return textureId;
    }
    const float rectangleVertices[] =
        {

            -1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f};

    // float rectangleVertices[] =
    //     {
    //         1.0f, -1.0f, 1.0f, 0.0f,
    //         -1.0f, -1.0f, 0.0f, 0.0f,
    //         -1.0f, 1.0f, 0.0f, 1.0f,

    //         1.0f, 1.0f, 1.0f, 1.0f,
    //         1.0f, -1.0f, 1.0f, 0.0f,
    //         -1.0f, 1.0f, 0.0f, 1.0f};

    GLuint createFramebufferVAO()
    {
        unsigned int rectVAO, rectVBO;
        glGenVertexArrays(1, &rectVAO);
        glGenBuffers(1, &rectVBO);
        glBindVertexArray(rectVAO);
        glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

        // unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        return rectVAO;
    }

    GLuint createRenderBuffer(const GLuint &fbo)
    {
        GLuint renderBufferId;
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glGenRenderbuffers(1, &renderBufferId);
        glBindRenderbuffer(GL_RENDERBUFFER, renderBufferId);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, viewportWidth, viewportHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferId);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return renderBufferId;
    }

    GLuint createFBO()
    {
        GLuint fbo;
        glGenFramebuffers(1, &fbo);
        return fbo;
    }
}

struct OpenGLPipeline::Internal
{
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

    Internal(const std::string &vertShaderName, const std::string &fragShaderName)
        : shader{hid::OpenGLShader(vertShaderName, fragShaderName)},
          defferedLightingProgram{hid::OpenGLShader("framebuffer", "deffered-lighting")},
          blurProgram{hid::OpenGLShader("framebuffer", "blur")},
          framebufferProgram{hid::OpenGLShader("framebuffer", "framebuffer")},
          animationProgram{hid::OpenGLShader("lit", "animation")},
          framebufferVAO{::createFramebufferVAO()},

          baseFBO{::createFBO()},
          positionTextureId(::createFramebufferTexture(baseFBO, GL_RGBA16F, GL_COLOR_ATTACHMENT0)),
          normalTextureId(::createFramebufferTexture(baseFBO, GL_RGBA16F, GL_COLOR_ATTACHMENT1)),
          albedoTextureId(::createFramebufferTexture(baseFBO, GL_RGBA16F, GL_COLOR_ATTACHMENT2)),
          depthRenderBufferId{::createRenderBuffer(baseFBO)},

          defferedLightingFBO(::createFBO()),
          baseTextureId{::createFramebufferTexture(defferedLightingFBO, GL_RGBA16F, GL_COLOR_ATTACHMENT0)},
          bloomTextureId{::createFramebufferTexture(defferedLightingFBO, GL_RGBA16F, GL_COLOR_ATTACHMENT1)},

          pingpongAmount{8}
    {

        // tell opengl use this attachment
        const GLuint baseAttatchments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
        glBindFramebuffer(GL_FRAMEBUFFER, baseFBO);
        glDrawBuffers(3, baseAttatchments);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        defferedLightingProgram.use();
        defferedLightingProgram.setInt("u_positionTexture", 0);
        defferedLightingProgram.setInt("u_normalTexture", 1);
        defferedLightingProgram.setInt("u_albedoTexture", 2);

        blurProgram.use();
        blurProgram.setInt("u_bloomTexture", 0);

        framebufferProgram.use();
        framebufferProgram.setInt("u_screenTexture", 0);
        framebufferProgram.setInt("u_bloomTexture", 1);

        const GLuint defferedLightingAttatchments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
        glBindFramebuffer(GL_FRAMEBUFFER, defferedLightingFBO);
        glDrawBuffers(2, defferedLightingAttatchments);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // pinpongFBO
        pingpongFBO[0] = ::createFBO();
        pingpongFBO[1] = ::createFBO();
        pingpongBufferTexture[0] = ::createFramebufferTexture(pingpongFBO[0], GL_RGBA16F, GL_COLOR_ATTACHMENT0);
        pingpongBufferTexture[1] = ::createFramebufferTexture(pingpongFBO[1], GL_RGBA16F, GL_COLOR_ATTACHMENT0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            return;
        }

        // frame buffer bind clear
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void render(
        const hid::OpenGLAssetManager &assetManager,
        const std::vector<hid::StaticMeshInstance> &staticMeshInstances,
        const hid::PerspectiveCamera &camera,
        const hid::LightSettings &lightSettings)
    {

        // geometry buffer
        glBindFramebuffer(GL_FRAMEBUFFER, baseFBO);

        // glClearColor(.8f, .8f, .8f, 0.0f);
        glClearColor(.0f, .0f, .0f, 1.0f);
        // glClearColor(.2f, .2f, .2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // basecolor pass
        shader.use();
        glActiveTexture(GL_TEXTURE0);
        shader.setMat4("u_projectionMatrix", &camera.getCameraMatrix()[0][0]);

        // for (const auto &staticMeshInstance : staticMeshInstances)
        // {
        //     shader.setMat4("u_modelMatrix", &staticMeshInstance.getModelMatrix()[0][0]);
        //     // const OpenGLTexture &albedo = assetManager.getTexture(staticMeshInstance.getTexture());
        //     hid::Material &mat = staticMeshInstance.getMaterial();

        //     assetManager.getTexture(mat.albedo).bind();
        //     // shader.setInt("u_sampler", 0);
        //     shader.setVec3("u_baseColor", &mat.baseColor[0]);
        //     assetManager.getStaticMesh(staticMeshInstance.getMesh()).draw();
        // }

        shader.setMat4("u_modelMatrix", &staticMeshInstances[3].getModelMatrix()[0][0]);
        hid::Material &mat2 = staticMeshInstances[3].getMaterial();
        assetManager.getTexture(mat2.albedo).bind();
        shader.setVec3("u_baseColor", &mat2.baseColor[0]);
        assetManager.getStaticMesh(staticMeshInstances[3].getMesh()).draw();

        animationProgram.use();
        glActiveTexture(GL_TEXTURE0);
        animationProgram.setMat4("u_projectionMatrix", &camera.getCameraMatrix()[0][0]);
        animationProgram.setMat4("u_modelMatrix", &staticMeshInstances[4].getModelMatrix()[0][0]);

        animationProgram.setInt("u_animationFrameX", animationFrame[animationCount]);
        if (frameCount < skipFrame)
        {
            ++frameCount;
        }
        else
        {
            frameCount = 0;
            ++animationCount;
            if (animationCount >= 4)
            {
                animationCount = 0;
            }
        }

        hid::Material &mat = staticMeshInstances[4].getMaterial();
        assetManager.getTexture(mat.albedo).bind();
        shader.setVec3("u_baseColor", &mat.baseColor[0]);
        assetManager.getStaticMesh(staticMeshInstances[4].getMesh()).draw();

        // deffered shading pass
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
        glBindFramebuffer(GL_FRAMEBUFFER, defferedLightingFBO);
        defferedLightingProgram.use();
        const hid::Light &pointLight = lightSettings.pointLight;
        const hid::Light &ambientLight = lightSettings.ambientLight;
        defferedLightingProgram.setVec3("u_pointLight[0].position", &pointLight.position[0]);
        defferedLightingProgram.setVec3("u_pointLight[0].color", &pointLight.color[0]);
        defferedLightingProgram.setFloat("u_pointLight[0].intensity", pointLight.intensity);
        defferedLightingProgram.setVec3("u_ambientLight.color", &ambientLight.color[0]);
        defferedLightingProgram.setFloat("u_ambientLight.intensity", ambientLight.intensity);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, positionTextureId);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normalTextureId);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, albedoTextureId);
        glBindVertexArray(framebufferVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // blur effect pass
        bool firstIteration = true;
        bool horizontal = true;
        blurProgram.use();
        for (int i = 0; i < pingpongAmount; ++i)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
            blurProgram.setInt("horizontal", horizontal);
            // for tatamikomi kawase
            blurProgram.setFloat("loopNum", (float)i + 1.0f);

            glActiveTexture(GL_TEXTURE0);
            if (firstIteration)
            {
                glBindTexture(GL_TEXTURE_2D, bloomTextureId);
                firstIteration = false;
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, pingpongBufferTexture[!horizontal]);
            }

            defferedLightingProgram.setInt("u_bloomTexture", 0);

            glBindVertexArray(framebufferVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            horizontal = !horizontal;
        }

        // framebuffer program
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        framebufferProgram.use();
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);

        framebufferProgram.setFloat("bloomIntensity", lightSettings.bloomIntensity);
        framebufferProgram.setBool("bloom", lightSettings.bloom);
        glBindVertexArray(framebufferVAO);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, baseTextureId);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, pingpongBufferTexture[!horizontal]);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    ~Internal()
    {
        shader.release();
    }
};

OpenGLPipeline::OpenGLPipeline(const std::string &vertShaderName, const std::string &fragShaderName)
    : internal(hid::make_internal_ptr<Internal>(vertShaderName, fragShaderName)) {}

void OpenGLPipeline::render(const hid::OpenGLAssetManager &assetManager,
                            const std::vector<hid::StaticMeshInstance> &staticMeshInstances,
                            const hid::PerspectiveCamera &camera,
                            const hid::LightSettings &lightSettings)
{
    internal->render(assetManager, staticMeshInstances, camera, lightSettings);
}