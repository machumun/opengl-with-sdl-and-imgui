#include "opengl-renderer.hpp"

using hid::OpenGLRenderer;

struct OpenGLRenderer::Internal
{
    const std::shared_ptr<hid::OpenGLAssetManager> assetManager;
    Internal(std::shared_ptr<hid::OpenGLAssetManager> assetManager) : assetManager(assetManager) {}

    void render(const hid::assets::Pipeline &pipeline,
                const std::shared_ptr<hid::Gui> &userData,
                const hid::PerspectiveCamera &camera)
    {
        assetManager->getPipeline(pipeline).render(*assetManager, userData, camera);
    }
};

OpenGLRenderer::OpenGLRenderer(std::shared_ptr<hid::OpenGLAssetManager> assetManager) : internal(hid::make_internal_ptr<Internal>(assetManager)) {}

void OpenGLRenderer::render(const hid::assets::Pipeline &pipeline,
                            const std::shared_ptr<hid::Gui> &userData,
                            const hid::PerspectiveCamera &camera)
{
    internal->render(pipeline, userData, camera);
}