#include "opengl_renderer.hpp"

using hid::OpenGLRenderer;

OpenGLRenderer::OpenGLRenderer(std::shared_ptr<hid::OpenGLAssetManager> assetManager) : assetManager(assetManager) {}

void OpenGLRenderer::render(const hid::assets::Pipeline &pipeline,
                            const std::shared_ptr<hid::Gui> &userData,
                            const hid::PerspectiveCamera &camera)
{
    assetManager->getPipeline(pipeline)->render(*assetManager, userData, camera);
}
