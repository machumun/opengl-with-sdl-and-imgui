#pragma once

#include "../../core/renderer.hpp"
#include "../../core/scene/scene_data.hpp"
#include "opengl_asset_manager.hpp"
#include <memory>

namespace hid
{
    struct OpenGLRenderer : public hid::Renderer
    {
        const std::shared_ptr<hid::OpenGLAssetManager> assetManager;

        OpenGLRenderer(std::shared_ptr<hid::OpenGLAssetManager> assetManager);

        void render(const hid::assets::Pipeline &pipeline) override;
        void setup(std::shared_ptr<hid::SceneData> sceneData) override;
    };
}