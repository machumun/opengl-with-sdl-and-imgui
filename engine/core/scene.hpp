#pragma once

#include "asset-manager.hpp"
#include "renderer.hpp"
#include "dat.hpp"

namespace hid
{

    struct Scene
    {
        Scene() = default;

        virtual ~Scene() = default;

        virtual void prepare(hid::AssetManager &assetManager,
                             const std::shared_ptr<hid::Dat> userData) = 0;

        virtual void update(const float &delta) = 0;

        virtual void render(hid::Renderer &renderer) = 0;
    };
} // namespace usr