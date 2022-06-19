#pragma once

#include "asset-inventory.hpp"
#include "gui/gui.hpp"
#include "perspective-camera.hpp"

#include <vector>

namespace hid
{
    struct Renderer
    {

        virtual void render(
            const hid::assets::Pipeline &pipeline,
            const std::shared_ptr<hid::Gui> &userData,
            const hid::PerspectiveCamera &camera) = 0;
    };
}