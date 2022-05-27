#include "opengl-pipeline.hpp"
#include "opengl-asset-manager.hpp"
#include "opengl-shader.hpp"

#include "../../core/assets.hpp"
#include "../../core/graphics-wrapper.hpp"

#include <stdexcept>
#include <vector>

using hid::OpenGLPipeline;

struct OpenGLPipeline::Internal
{
    const hid::OpenGLShader shader;

    // texcoordはvectorの0,1,2の後3から始まるため3 * sizeof(float)
    Internal(const std::string &shaderName)
        : shader(hid::OpenGLShader(shaderName))
    {
    }

    void render(
        const hid::OpenGLAssetManager &assetManager,
        const std::vector<hid::StaticMeshInstance> &staticMeshInstances,
        const hid::PerspectiveCamera &camera) const
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
        const hid::LightSettings &lightSettings) const
    {
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
            assetManager.getTexture(staticMeshInstance.getTexture()).bind();
            assetManager.getStaticMesh(staticMeshInstance.getMesh()).draw();
        }
    }

    ~Internal()
    {
        shader.release();
    }
};

OpenGLPipeline::OpenGLPipeline(const std::string &shaderName) : internal(hid::make_internal_ptr<Internal>(shaderName)) {}

void OpenGLPipeline::render(const hid::OpenGLAssetManager &assetManager,
                            const std::vector<hid::StaticMeshInstance> &staticMeshInstances,
                            const hid::PerspectiveCamera &camera) const
{
    internal->render(assetManager, staticMeshInstances, camera);
}

void OpenGLPipeline::render(const hid::OpenGLAssetManager &assetManager,
                            const std::vector<hid::StaticMeshInstance> &staticMeshInstances,
                            const hid::PerspectiveCamera &camera,
                            const hid::LightSettings &lightSettings) const
{
    internal->render(assetManager, staticMeshInstances, camera, lightSettings);
}