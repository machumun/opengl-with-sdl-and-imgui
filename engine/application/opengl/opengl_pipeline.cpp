#include "opengl_pipeline.hpp"
#include "opengl_asset_manager.hpp"

#include "../../core/asset_loader.hpp"
#include "../../core/wrapper/graphics_wrapper.hpp"
#include "../../core/log.hpp"

#include "../../core/object.hpp"

#include <stdexcept>
#include <vector>

// debug
// #include <typeinfo>
// #include <iostream>

namespace
{
    float packedMaterialFlags(uint32_t materialFlags)
    {
        return materialFlags * (1.f / 255.f);
    }

    uint32_t unpackMaterialFlags(float packedMaterialFlags)
    {
        return uint32_t((packedMaterialFlags * 255.0f) + 0.5f);
    }
}

using hid::OpenGLPipeline;

namespace
{
    uint32_t viewportWidth = hid::sdl::getDisplaySize().first;
    uint32_t viewportHeight = hid::sdl::getDisplaySize().second;

    GLuint createFramebufferTexture(const GLuint &fbo,
                                    const GLuint &internalFormat,
                                    const GLuint &format,
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
                     format,
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

OpenGLPipeline::OpenGLPipeline()

    : defferedLightingProgram{hid::OpenGLShader("assets/shaders/opengl/framebuffer.vert", "assets/shaders/opengl/deffered_lighting.frag")},
      blurProgram{hid::OpenGLShader("assets/shaders/opengl/framebuffer.vert", "assets/shaders/opengl/blur.frag")},
      framebufferProgram{hid::OpenGLShader("assets/shaders/opengl/framebuffer.vert", "assets/shaders/opengl/framebuffer.frag")},

      framebufferVAO{::createFramebufferVAO()},
      renderFBO{::createFBO()},
      renderTextureId(::createFramebufferTexture(renderFBO, GL_RGBA16F, GL_RGBA, GL_COLOR_ATTACHMENT0)),
      baseFBO{::createFBO()},
      positionTextureId{::createFramebufferTexture(baseFBO, GL_RGB16F, GL_RGB, GL_COLOR_ATTACHMENT0)},
      normalTextureId{::createFramebufferTexture(baseFBO, GL_RGB16F, GL_RGB, GL_COLOR_ATTACHMENT1)},
      albedoTextureId{::createFramebufferTexture(baseFBO, GL_RGBA16F, GL_RGBA, GL_COLOR_ATTACHMENT2)},
      //   lightingMaskTextureId{::createFramebufferTexture(baseFBO, GL_R8, GL_R, GL_COLOR_ATTACHMENT3)},
      depthRenderBufferId{::createRenderBuffer(baseFBO)},

      defferedLightingFBO{::createFBO()},
      baseTextureId{::createFramebufferTexture(defferedLightingFBO, GL_RGB16F, GL_RGB, GL_COLOR_ATTACHMENT0)},
      bloomTextureId{::createFramebufferTexture(defferedLightingFBO, GL_RGB16F, GL_RGB, GL_COLOR_ATTACHMENT1)},

      pingpongAmount{8}
{

    // tell opengl use this attachment
    const GLuint baseAttatchments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    glBindFramebuffer(GL_FRAMEBUFFER, baseFBO);
    glDrawBuffers(3, baseAttatchments);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    defferedLightingProgram.useProgram();
    // in uniforms
    defferedLightingProgram.setInt("u_positionTexture", 0);
    defferedLightingProgram.setInt("u_normalTexture", 1);
    defferedLightingProgram.setInt("u_albedoTexture", 2);
    // defferedLightingProgram.setInt("u_lightingMask", 3);

    blurProgram.useProgram();
    blurProgram.setInt("u_bloomTexture", 0);

    framebufferProgram.useProgram();
    // in uniforms
    framebufferProgram.setInt("u_screenTexture", 0);
    framebufferProgram.setInt("u_bloomTexture", 1);

    const GLuint defferedLightingAttatchments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glBindFramebuffer(GL_FRAMEBUFFER, defferedLightingFBO);
    glDrawBuffers(2, defferedLightingAttatchments);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // pinpongFBO
    pingpongFBO[0] = ::createFBO();
    pingpongFBO[1] = ::createFBO();
    pingpongBufferTexture[0] = ::createFramebufferTexture(pingpongFBO[0], GL_RGBA16F, GL_RGBA, GL_COLOR_ATTACHMENT0);
    pingpongBufferTexture[1] = ::createFramebufferTexture(pingpongFBO[1], GL_RGBA16F, GL_RGBA, GL_COLOR_ATTACHMENT0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        return;
    }

    // frame buffer bind to default
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLPipeline::render()
{

    const static std::string logTag{"hid::OpenGLPipeline::render"};
    // geometry buffer
    glBindFramebuffer(GL_FRAMEBUFFER, baseFBO);

    // glClearColor(.8f, .8f, .8f, 1.0f);
    // glClearColor(.3f, .3f, .3f, 1.f);
    glClearColor(camera->background.r,
                 camera->background.g,
                 camera->background.b,
                 0.f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // as a g buffer pass
    for (auto &&object : sceneData->objects)
    {
        object->draw();
    }

    // deffered lighting pass

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glBindFramebuffer(GL_FRAMEBUFFER, defferedLightingFBO);

    defferedLightingProgram.useProgram();

    const size_t &lightNum = pointLights.size();

    for (GLuint i = 0; i < lightNum; ++i)
    {
        defferedLightingProgram.setVec3("u_pointLight[" + std::to_string(i) + "].position", &pointLights[i]->transform->position[0]);
        defferedLightingProgram.setVec3("u_pointLight[" + std::to_string(i) + "].color", &pointLights[i]->color[0]);
        defferedLightingProgram.setFloat("u_pointLight[" + std::to_string(i) + "].intensity", pointLights[i]->intensity);
    }

    defferedLightingProgram.setVec3("u_ambientLight.color", &sceneData->environmentalSettings->ambientColor[0]);
    defferedLightingProgram.setFloat("u_ambientLight.intensity", sceneData->environmentalSettings->ambientIntencity);
    defferedLightingProgram.setFloat("u_threshold", sceneData->environmentalSettings->bloomThreshold);

    defferedLightingProgram.setVec4("u_backgroundColor", &camera->background[0]);

    // in uniforms
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

    if (sceneData->environmentalSettings->postProcessing)
    {
        blurProgram.useProgram();
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
    }

    // default framebuffer program
    glBindFramebuffer(GL_FRAMEBUFFER, renderFBO);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
    framebufferProgram.useProgram();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    framebufferProgram.setFloat("bloomIntensity", sceneData->environmentalSettings->bloomStrength);
    framebufferProgram.setBool("bloom", sceneData->environmentalSettings->postProcessing);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, baseTextureId);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, pingpongBufferTexture[!horizontal]);

    glBindVertexArray(framebufferVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // glBindVertexArray(framebufferVAO);
    // glDrawArrays(GL_TRIANGLES, 0, 6);
}

void OpenGLPipeline::setup(const std::shared_ptr<hid::SceneData> &sceneData)
{
    static std::string logTag{"hid::OpenGLPipeline::setup"};

    this->sceneData = sceneData;

    // for runtime
    for (auto &object : this->sceneData->objects)
    {
        if (object->hasComponent<hid::Camera>())
        {
            camera = &object->getComponent<Camera>();
        }
        if (object->hasComponent<Light>())
        {
            if (object->getComponent<Light>().lightType == hid::LightType::Point)
            {
                hid::log(logTag, "Point Light was found.");
                pointLights.emplace_back(&object->getComponent<Light>());
            }
        }
    }
}

OpenGLPipeline::~OpenGLPipeline()
{
    defferedLightingProgram.release();
    blurProgram.release();
    framebufferProgram.release();
}

void OpenGLPipeline::resize(const GLuint &width, const GLuint &height)
{
}
