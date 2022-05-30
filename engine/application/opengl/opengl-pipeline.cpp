#include "opengl-pipeline.hpp"
#include "opengl-asset-manager.hpp"
#include "opengl-shader.hpp"

#include "../../core/assets.hpp"
#include "../../core/graphics-wrapper.hpp"
#include "../../core/log.hpp"

#include <stdexcept>
#include <vector>

using hid::OpenGLPipeline;

namespace
{
    uint32_t viewportWidth = hid::sdl::getDisplaySize().first;
    uint32_t viewportHeight = hid::sdl::getDisplaySize().second;
    GLuint createFramebufferTexture(GLuint attachment)
    {

        static const std::string logTag{"hid::OpenGLApplication::createFramebufferTexture"};
        GLuint textureId;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGB16F,
                     viewportWidth,
                     viewportHeight,
                     0,
                     GL_RGB,
                     GL_UNSIGNED_BYTE,
                     NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, textureId, 0);

        hid::log(logTag, "Created Framebuffer Texture: " + attachment + std::to_string(viewportWidth) + " x " + std::to_string(viewportHeight));

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

        return rectVAO;
    }

    GLuint createFBO()
    {
        GLuint fbo;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        return fbo;
    }
}

struct OpenGLPipeline::Internal
{
    const hid::OpenGLShader shader;
    const hid::OpenGLShader blurProgram;
    const hid::OpenGLShader framebufferProgram;

    const float gamma;

    const GLuint postProcessingFBO;

    const GLuint postProcessingTextureId;
    const GLuint bloomTextureId;

    const GLuint framebufferVAO;

    GLuint pingpongFBO[2];
    GLuint pingpongBuffer[2];

    // texcoordはvectorの0,1,2の後3から始まるため3 * sizeof(float)
    Internal(const std::string &vertShaderName, const std::string &fragShaderName)
        : shader(hid::OpenGLShader(vertShaderName, fragShaderName)),
          blurProgram(hid::OpenGLShader("framebuffer", "blur")),
          framebufferProgram(hid::OpenGLShader("framebuffer", "framebuffer")),
          framebufferVAO(::createFramebufferVAO()),
          postProcessingFBO(::createFBO()),
          bloomTextureId(::createFramebufferTexture(GL_COLOR_ATTACHMENT0)),
          postProcessingTextureId(::createFramebufferTexture(GL_COLOR_ATTACHMENT1)),
          gamma(2.2f)
    {
        framebufferProgram.use();
        framebufferProgram.setInt("u_screenTexture", 0);
        framebufferProgram.setInt("u_bloomTexture", 1);
        framebufferProgram.setFloat("gamma", gamma);

        blurProgram.use();
        blurProgram.setInt("u_screenTexture", 0);

        GLuint attatchments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};

        // tell opengl use this attachment
        glDrawBuffers(2, attatchments);

        // create pingpong framebuffer for repetitive bluring
        glGenFramebuffers(2, pingpongFBO);
        glGenTextures(2, pingpongBuffer);

        for (int i = 0; i < 2; ++i)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
            glBindTexture(GL_TEXTURE_2D, pingpongBuffer[i]);
            glTexImage2D(GL_TEXTURE_2D,
                         0, GL_RGBA16F,
                         ::viewportWidth,
                         ::viewportHeight,
                         0, GL_RGB,
                         GL_UNSIGNED_BYTE,
                         NULL);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_COLOR_ATTACHMENT0,
                                   GL_TEXTURE_2D,
                                   pingpongBuffer[i],
                                   0);
        }
    }

    void render(
        const hid::OpenGLAssetManager &assetManager,
        const std::vector<hid::StaticMeshInstance> &staticMeshInstances,
        const hid::PerspectiveCamera &camera)
    {
        shader.use();
        shader.setMat4("u_projectionMatrix", &camera.getCameraMatrix()[0][0]);

        for (const auto &staticMeshInstance : staticMeshInstances)
        {
            shader.setMat4("u_modelMatrix", &staticMeshInstance.getModelMatrix()[0][0]);
            assetManager.getTexture(staticMeshInstance.getTexture()).bind();
            assetManager.getStaticMesh(staticMeshInstance.getMesh()).draw();
        }
    }

    void render(
        const hid::OpenGLAssetManager &assetManager,
        const std::vector<hid::StaticMeshInstance> &staticMeshInstances,
        const hid::PerspectiveCamera &camera,
        const hid::LightSettings &lightSettings)
    {

        // bind postprocess framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, postProcessingFBO);
        // glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClearColor(0.0f, .0f, .0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glEnable(GL_DEPTH_TEST);

        // draw the normal models
        shader.use();

        const hid::Light &pointLight = lightSettings.pointLight;
        const hid::Light &ambientLight = lightSettings.ambientLight;
        shader.setVec3("u_pointLightPosition", &pointLight.position[0]);
        shader.setVec4("u_pointLightColor", &pointLight.color[0]);
        shader.setFloat("u_pointLightStrength", pointLight.strength);
        shader.setVec4("u_ambientLightColor", &ambientLight.color[0]);
        shader.setFloat("u_ambientLightStrength", ambientLight.strength);

        shader.setMat4("u_projectionMatrix", &camera.getCameraMatrix()[0][0]);

        for (const auto &staticMeshInstance : staticMeshInstances)
        {
            shader.setMat4("u_modelMatrix", &staticMeshInstance.getModelMatrix()[0][0]);
            const OpenGLTexture &albedo = assetManager.getTexture(staticMeshInstance.getTexture());
            albedo.bind();
            shader.setInt("u_sampler", 1);
            assetManager.getStaticMesh(staticMeshInstance.getMesh()).draw();
        }

        // blur pass

        bool firstIteration = true;
        bool horizontal = true;
        int amount = 8;
        blurProgram.use();
        for (int i = 0; i < amount; ++i)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
            blurProgram.setInt("horizontal", horizontal);
            if (firstIteration)
            {
                glBindTexture(GL_TEXTURE_2D, bloomTextureId);
                firstIteration = false;
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, pingpongBuffer[!horizontal]);
            }
            // Render the image
            glBindVertexArray(framebufferVAO);
            glDisable(GL_DEPTH_TEST);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            // Switch between vertical and horizontal blurring if (horizontal)

            horizontal = !horizontal;
        }

        // framebuffer program

        // // Bind the default framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // // Draw the framebuffer rectangle

        framebufferProgram.use();
        glBindVertexArray(framebufferVAO);
        glDisable(GL_DEPTH_TEST);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, postProcessingTextureId);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, pingpongBuffer[!horizontal]);
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
                            const hid::PerspectiveCamera &camera)
{
    internal->render(assetManager, staticMeshInstances, camera);
}

void OpenGLPipeline::render(const hid::OpenGLAssetManager &assetManager,
                            const std::vector<hid::StaticMeshInstance> &staticMeshInstances,
                            const hid::PerspectiveCamera &camera,
                            const hid::LightSettings &lightSettings)
{
    internal->render(assetManager, staticMeshInstances, camera, lightSettings);
}