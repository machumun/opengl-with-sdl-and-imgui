#pragma once

#include "../../core/internal-ptr.hpp"
#include "../../core/light-settings.hpp"
#include "../../core/static-mesh-instance.hpp"
#include "../../core/perspective-camera.hpp"
#include <string>
#include <vector>

namespace hid
{
    struct OpenGLAssetManager;

    struct OpenGLPipeline
    {
        OpenGLPipeline(const std::string &shaderName);

        // unlit
        void render(
            const hid::OpenGLAssetManager &assetManager,
            const std::vector<hid::StaticMeshInstance> &staticMeshInstances,
            const hid::PerspectiveCamera &camera) const;

        void render(
            const hid::OpenGLAssetManager &assetManager,
            const std::vector<hid::StaticMeshInstance> &staticMeshInstances,
            const hid::PerspectiveCamera &camera,
            const hid::LightSettings &lightSettings) const;

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
}