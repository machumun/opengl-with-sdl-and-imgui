#pragma once

#include "asset-manager.hpp"
#include "renderer.hpp"
#include "dat.hpp"

namespace hid
{

    struct Scene
    {

        std::shared_ptr<hid::Dat> sceneData;

        Scene(std::shared_ptr<hid::Dat> &userData)
            : sceneData(userData){};

        virtual ~Scene() = default;

        virtual void prepare(hid::AssetManager &assetManager) = 0;

        virtual void update(const float &delta) = 0;

        virtual void render(hid::Renderer &renderer) = 0;
    };
} // namespace usr