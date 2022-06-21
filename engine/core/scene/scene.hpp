#pragma once

#include "scene_data.hpp"

#include "../asset_manager.hpp"
#include "../renderer.hpp"

#include "../object.hpp"

namespace hid
{

    struct Scene
    {

        std::shared_ptr<hid::SceneData> sceneData;

        Scene() : sceneData{std::make_shared<hid::SceneData>()} {}
        virtual ~Scene() = default;

        virtual void prepare(hid::AssetManager &assetManager) = 0;

        virtual void update(const float &delta) = 0;

        virtual void render(hid::Renderer &renderer) = 0;

        void instantiate(std::unique_ptr<hid::Object> object);
    };
} // namespace usr