#pragma once

#include "../../engine/core/scene/scene.hpp"

#include "../../engine/core/wrapper/sdl_wrapper.hpp"

#include "../../core/components/player_controller.hpp"

namespace hid
{
    struct SceneMain : public hid::Scene
    {

        hid::PlayerController* playerController;

        SceneMain() = default;

        void prepare() override;
        void update(const float& delta) override;

        void render(const hid::Renderer& renderer) override;
    };
} // namespace hid