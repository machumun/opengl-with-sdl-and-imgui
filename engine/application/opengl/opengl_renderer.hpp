#pragma once

#include "../../core/renderer.hpp"
#include "../../core/gui/gui.hpp"
#include "opengl_asset_manager.hpp"
#include <memory>

namespace hid
{
    struct OpenGLRenderer : public hid::Renderer
    {
        const std::shared_ptr<hid::OpenGLAssetManager> assetManager;

        OpenGLRenderer(std::shared_ptr<hid::OpenGLAssetManager> assetManager);

        void render(
            const hid::assets::Pipeline &pipeline,
            const std::shared_ptr<hid::Gui> &userData,
            const hid::PerspectiveCamera &camera) override;
    };
}