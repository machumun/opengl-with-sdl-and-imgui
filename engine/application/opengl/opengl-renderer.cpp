#include "opengl-renderer.hpp"

using hid::OpenGLRenderer;

struct OpenGLRenderer::Internal
{
    const std::shared_ptr<hid::OpenGLAssetManager> assetManager;
    Internal(std::shared_ptr<hid::OpenGLAssetManager> assetManager) : assetManager(assetManager) {}

    void render(const hid::assets::Pipeline &pipeline,
                const std::vector<hid::StaticMeshInstance> &staticMeshInstances,
                const hid::PerspectiveCamera &camera)
    {
        assetManager->getPipeline(pipeline).render(*assetManager, staticMeshInstances, camera);
    }

    void render(const hid::assets::Pipeline &pipeline,
                const std::vector<hid::StaticMeshInstance> &staticMeshInstances,
                const hid::PerspectiveCamera &camera,
                const hid::LightSettings &lightSettings)
    {
        assetManager->getPipeline(pipeline).render(*assetManager, staticMeshInstances, camera, lightSettings);
    }
};

OpenGLRenderer::OpenGLRenderer(std::shared_ptr<hid::OpenGLAssetManager> assetManager) : internal(hid::make_internal_ptr<Internal>(assetManager)) {}

void OpenGLRenderer::render(const hid::assets::Pipeline &pipeline,
                            const std::vector<hid::StaticMeshInstance> &staticMeshInstances,
                            const hid::PerspectiveCamera &camera)
{
    internal->render(pipeline, staticMeshInstances, camera);
}

void OpenGLRenderer::render(const hid::assets::Pipeline &pipeline,
                            const std::vector<hid::StaticMeshInstance> &staticMeshInstances,
                            const hid::PerspectiveCamera &camera,
                            const hid::LightSettings &lightSettings)
{
    internal->render(pipeline, staticMeshInstances, camera, lightSettings);
}