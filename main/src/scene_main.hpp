#pragma once

#include "../../engine/core/scene/scene.hpp"

#include "../../engine/core/light_settings.hpp"
#include "../../engine/core/perspective_camera.hpp"
#include "../../engine/core/wrapper/sdl_wrapper.hpp"

#include "player.hpp"

namespace
{
    hid::PerspectiveCamera createCamera()
    {
        std::pair<uint32_t, uint32_t> displaySize{hid::sdl::getDisplaySize()};
        return hid::PerspectiveCamera(displaySize.first, displaySize.second);
    }
} // namespace

namespace hid
{
    struct SceneMain : public hid::Scene
    {
        hid::PerspectiveCamera camera;

        hid::Player player;

        const uint8_t* keyboardState;

        SceneMain::SceneMain()
            : camera(::createCamera()),
              player(hid::Player(glm::vec3{0.0f, 0.0f, 2.0f}, 0.0f)),
              keyboardState(SDL_GetKeyboardState(nullptr)) {}

        void prepare(hid::AssetManager& assetManager) override;

        void update(const float& delta) override;

        void render(hid::Renderer& renderer) override;

        void input(const float& delta);
    };
} // namespace hid