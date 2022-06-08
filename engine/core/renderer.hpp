#pragma once

#include "asset-inventory.hpp"
#include "dat.hpp"
#include "perspective-camera.hpp"

#include <vector>

namespace hid
{
    struct Renderer
    {

        virtual void render(
            const hid::assets::Pipeline &pipeline,
            const std::shared_ptr<hid::Dat> &userData,
            const hid::PerspectiveCamera &camera) = 0;
    };
}