#pragma once

#include "../../core/renderer.hpp"
#include "../../core/scene/scene_data.hpp"
#include "opengl_asset_manager.hpp"
#include <memory>

namespace hid
{
    struct OpenGLRenderer : public hid::Renderer
    {
        std::unique_ptr<hid::OpenGLPipeline> standardPipeline;

        OpenGLRenderer()
            : standardPipeline{std::make_unique<hid::OpenGLPipeline>()} {}

        void render(const hid::assets::Pipeline &pipeline) override;
        void setup(std::shared_ptr<hid::SceneData> sceneData) override;
    };
}