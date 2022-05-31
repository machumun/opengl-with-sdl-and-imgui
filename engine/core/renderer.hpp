#pragma once

#include "asset-inventory.hpp"
#include "static-mesh-instance.hpp"
#include "light-settings.hpp"
#include "perspective-camera.hpp"

#include <vector>

namespace hid
{
    struct Renderer
    {

        virtual void render(
            const hid::assets::Pipeline &pipeline,
            const std::vector<hid::StaticMeshInstance> &staticMeshInstances,
            const hid::PerspectiveCamera &camera,
            const hid::LightSettings &lightSettings) = 0;
    };
}