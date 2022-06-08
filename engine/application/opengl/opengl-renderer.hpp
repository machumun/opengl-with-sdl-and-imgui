#pragma once

#include "../../core/internal-ptr.hpp"
#include "../../core/renderer.hpp"
#include "../../core/dat.hpp"
#include "opengl-asset-manager.hpp"
#include <memory>

namespace hid
{
    struct OpenGLRenderer : public hid::Renderer
    {
        OpenGLRenderer(std::shared_ptr<hid::OpenGLAssetManager> assetManager);

        void render(
            const hid::assets::Pipeline &pipeline,
            const std::shared_ptr<hid::Dat> &userData,
            const hid::PerspectiveCamera &camera) override;

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
}