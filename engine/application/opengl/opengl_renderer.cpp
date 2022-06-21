#include "opengl_renderer.hpp"

using hid::OpenGLRenderer;

OpenGLRenderer::OpenGLRenderer(std::shared_ptr<hid::OpenGLAssetManager> assetManager) : assetManager(assetManager) {}

void OpenGLRenderer::render(const hid::assets::Pipeline &pipeline,
                            const std::shared_ptr<hid::SceneData> &sceneData,
                            const hid::PerspectiveCamera &camera)
{
    assetManager->getPipeline(pipeline)->render(*assetManager, sceneData, camera);
}
