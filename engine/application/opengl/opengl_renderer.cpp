#include "opengl_renderer.hpp"

using hid::OpenGLRenderer;

const void OpenGLRenderer::render() const
{
    standardPipeline->render();
}

void OpenGLRenderer::setup(std::shared_ptr<hid::SceneData> sceneData)
{
    standardPipeline->setup(sceneData);
}
