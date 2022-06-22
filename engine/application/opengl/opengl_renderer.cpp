#include "opengl_renderer.hpp"

using hid::OpenGLRenderer;

OpenGLRenderer::OpenGLRenderer(std::shared_ptr<hid::OpenGLAssetManager> assetManager) : assetManager(assetManager) {}

void OpenGLRenderer::render(const hid::assets::Pipeline &pipeline)
{
    assetManager->getPipeline(pipeline)->render(*assetManager);
}

void OpenGLRenderer::setup(std::shared_ptr<hid::SceneData> sceneData)
{
    hid::assets::Pipeline pipeline = hid::assets::Pipeline::LitPass;
    assetManager->getPipeline(pipeline)->setup(sceneData);
}
