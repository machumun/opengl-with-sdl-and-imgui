#pragma once

#include "../../engine/core/dat.hpp"
#include "../../engine/core/scene.hpp"

#include "../../engine/core/animation-plane.hpp"
#include "../../engine/core/light-settings.hpp"
#include "../../engine/core/perspective-camera.hpp"
#include "../../engine/core/sdl-wrapper.hpp"
#include "../../engine/core/static-mesh-instance.hpp"

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

        SceneMain::SceneMain(std::shared_ptr<hid::Dat>& userData)
            : Scene(userData),
              camera(::createCamera()),
              player(hid::Player(glm::vec3{0.0f, 0.0f, 2.0f}, 0.0f)),
              keyboardState(SDL_GetKeyboardState(nullptr)) {}

        void prepare(hid::AssetManager& assetManager) override;

        void update(const float& delta) override;

        void render(hid::Renderer& renderer) override;

        void input(const float& delta);
    };
} // namespace hid