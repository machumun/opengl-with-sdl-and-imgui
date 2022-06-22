#pragma once

#include "asset_inventory.hpp"
#include "scene/scene_data.hpp"

#include <vector>

namespace hid
{
    struct Renderer
    {
        virtual void render(const hid::assets::Pipeline &pipeline) = 0;
        virtual void setup(std::shared_ptr<hid::SceneData> sceneData) = 0;
    };
}