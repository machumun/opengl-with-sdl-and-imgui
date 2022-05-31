#pragma once

#include "../../core/internal-ptr.hpp"
#include "../../core/renderer.hpp"
#include "opengl-asset-manager.hpp"
#include <memory>

namespace hid
{
    struct OpenGLRenderer : public hid::Renderer
    {
        OpenGLRenderer(std::shared_ptr<hid::OpenGLAssetManager> assetManager);

        void render(const hid::assets::Pipeline &pipeline,
                    const std::vector<hid::StaticMeshInstance> &staticMeshInstances,
                    const hid::PerspectiveCamera &camera,
                    const hid::LightSettings &lightSettings) override;

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
}