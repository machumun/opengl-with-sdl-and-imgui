#pragma once

#include "asset_inventory.hpp"
#include "scene/scene_data.hpp"
#include "perspective_camera.hpp"

#include <vector>

namespace hid
{
    struct Renderer
    {
        virtual void render(
            const hid::assets::Pipeline &pipeline,
            const std::shared_ptr<hid::SceneData> &sceneData,
            const hid::PerspectiveCamera &camera) = 0;
    };
}