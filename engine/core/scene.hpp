#pragma once

#include "asset_manager.hpp"
#include "renderer.hpp"
#include "gui/gui.hpp"

namespace hid
{

    struct Scene
    {

        std::shared_ptr<hid::Gui> sceneData;

        Scene(std::shared_ptr<hid::Gui> &userData)
            : sceneData(userData){};

        virtual ~Scene() = default;

        virtual void prepare(hid::AssetManager &assetManager) = 0;

        virtual void update(const float &delta) = 0;

        virtual void render(hid::Renderer &renderer) = 0;
    };
} // namespace usr