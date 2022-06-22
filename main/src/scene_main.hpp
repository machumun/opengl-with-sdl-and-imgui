#pragma once

#include "../../engine/core/scene/scene.hpp"

#include "../../engine/core/light_settings.hpp"

#include "../../engine/core/wrapper/sdl_wrapper.hpp"

#include "player.hpp"

namespace hid
{
    struct SceneMain : public hid::Scene
    {

        hid::Player player;

        const uint8_t* keyboardState;

        SceneMain::SceneMain()
            : player(hid::Player(glm::vec3{0.0f, 0.0f, 2.0f}, 0.0f)),
              keyboardState(SDL_GetKeyboardState(nullptr)) {}

        void prepare(hid::AssetManager& assetManager) override;

        void update(const float& delta) override;

        void render(hid::Renderer& renderer) override;

        void input(const float& delta);
    };
} // namespace hid