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
    const hid::OpenGLShader blurProgram;
    const hid::OpenGLShader framebufferProgram;

    const GLuint postProcessingFBO;

    const GLuint postProcessingTextureId;
    const GLuint bloomTextureId;

    const GLuint depthRenderBufferId;

    const GLuint framebufferVAO;

    GLuint pingpongFBO[2];
    GLuint pingpongBufferTexture[2];
    GLuint pingpongDepthRenderBufferId[2];

    const GLuint attatchments[2];

    const int pingpongAmount;

    Internal(const std::string &vertShaderName, const std::string &fragShaderName)
        : shader{hid::OpenGLShader(vertShaderName, fragShaderName)},
          blurProgram{hid::OpenGLShader("framebuffer", "blur")},
          framebufferProgram{hid::OpenGLShader("framebuffer", "framebuffer")},
          framebufferVAO{::createFramebufferVAO()},

          postProcessingFBO{::createFBO()},
          postProcessingTextureId{::createFramebufferTexture(postProcessingFBO, GL_RGBA16F, GL_COLOR_ATTACHMENT0)},
          bloomTextureId{::createFramebufferTexture(postProcessingFBO, GL_RGBA16F, GL_COLOR_ATTACHMENT1)},
          depthRenderBufferId{::createRenderBuffer(postProcessingFBO)},

          pingpongAmount{10},
          attatchments{GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1}
    {

        framebufferProgram.use();
        framebufferProgram.setInt("u_screenTexture", 0);
        framebufferProgram.setInt("u_bloomTexture", 1);

        blurProgram.use();
        blurProgram.setInt("u_bloomTexture", 1);

        // tell opengl use this attachment
        glBindFramebuffer(GL_FRAMEBUFFER, postProcessingFBO);
        glDrawBuffers(2, attatchments);
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

        // bind postprocess framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, postProcessingFBO);

        // glClearColor(.8f, .8f, .8f, 1.0f);
        // glClearColor(.0f, .0f, .0f, 1.0f);
        glClearColor(.2f, .2f, .2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glDepthFunc(GL_LEQUAL);

        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // draw the normal models
        shader.use();

        const hid::Light &pointLight = lightSettings.pointLight;
        const hid::Light &ambientLight = lightSettings.ambientLight;
        shader.setVec3("u_pointLight[0].position", &pointLight.position[0]);
        shader.setVec3("u_pointLight[0].color", &pointLight.color[0]);
        shader.setFloat("u_pointLight[0].intensity", pointLight.intensity);
        shader.setVec3("u_ambientLight.color", &ambientLight.color[0]);
        shader.setFloat("u_ambientLight.intensity", ambientLight.intensity);

        shader.setMat4("u_projectionMatrix", &camera.getCameraMatrix()[0][0]);

        for (const auto &staticMeshInstance : staticMeshInstances)
        {
            shader.setMat4("u_modelMatrix", &staticMeshInstance.getModelMatrix()[0][0]);
            // const OpenGLTexture &albedo = assetManager.getTexture(staticMeshInstance.getTexture());
            hid::Material &mat = staticMeshInstance.getMaterial();
            assetManager.getTexture(mat.albedo).bind();
            shader.setInt("u_sampler", 1);
            shader.setVec3("u_baseColor", &mat.baseColor[0]);
            assetManager.getStaticMesh(staticMeshInstance.getMesh()).draw();
        }

                // blur pass
        bool firstIteration = true;
        bool horizontal = true;
        blurProgram.use();
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
        for (int i = 0; i < pingpongAmount; ++i)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
            blurProgram.setInt("horizontal", horizontal);
            // for tatamikomi kawase
            blurProgram.setFloat("loopNum", (float)i + 1.0f);

            if (firstIteration)
            {
                // hid::log("hid::OpenGLApplication::render: blur loop:", std::to_string(i));
                glBindTexture(GL_TEXTURE_2D, bloomTextureId);
                firstIteration = false;
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, pingpongBufferTexture[!horizontal]);
            }

            glBindVertexArray(framebufferVAO);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            horizontal = !horizontal;
        }

        // framebuffer program
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        framebufferProgram.use();
        framebufferProgram.setFloat("bloomIntensity", lightSettings.bloomIntensity);
        framebufferProgram.setBool("bloom", lightSettings.bloom);
        glBindVertexArray(framebufferVAO);
        // glDisable(GL_DEPTH_TEST);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, postProcessingTextureId);
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