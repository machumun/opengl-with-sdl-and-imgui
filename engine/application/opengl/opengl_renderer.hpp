#pragma once

#include "../../core/renderer.hpp"
#include "../../core/scene/scene_data.hpp"
#include "opengl_asset_manager.hpp"
#include <memory>

namespace hid
{
    struct OpenGLRenderer : public hid::Renderer
    {

        const std::unique_ptr<hid::OpenGLPipeline> standardPipeline;

        OpenGLRenderer()
            : standardPipeline{std::make_unique<hid::OpenGLPipeline>()} {}

        const void render() const override;
        void setup(std::shared_ptr<hid::SceneData> sceneData) override;
    };
}