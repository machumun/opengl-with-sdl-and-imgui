#include "opengl_renderer.hpp"

using hid::OpenGLRenderer;

void OpenGLRenderer::render(const hid::assets::Pipeline &pipeline)
{
    standardPipeline->render();
}

void OpenGLRenderer::setup(std::shared_ptr<hid::SceneData> sceneData)
{
    standardPipeline->setup(sceneData);
}
