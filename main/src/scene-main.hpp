#pragma once

#include "../../engine/core/dat.hpp"
#include "../../engine/core/internal-ptr.hpp"
#include "../../engine/core/scene.hpp"

namespace usr
{

    struct SceneMain : public hid::Scene
    {
        SceneMain(const float& screenWidth, const float& screenHeight);

        void prepare(hid::AssetManager& assetManager,
                     std::shared_ptr<hid::Dat>& userData) override;

        void update(const float& delta) override;

        void render(hid::Renderer& renderer) override;

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
} // namespace usr