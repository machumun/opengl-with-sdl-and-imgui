#pragma once

#include "opengl-imgui.hpp"
#include "opengl-asset-manager.hpp"
#include "opengl-renderer.hpp"

#include "../../../main/src/scene-main.hpp"
#include "../application.hpp"

namespace hid
{
    struct OpenGLApplication : public hid::Application
    {

        OpenGLApplication();
        ~OpenGLApplication();
        void update(const float &delta) override;
        void render() override;

        void init() override;

        hid::Scene &getScene();

    private:
        SDL_Window *window;
        SDL_GLContext context;
        std::unique_ptr<hid::OpenGLImGui> imgui;
        const std::shared_ptr<hid::OpenGLAssetManager> assetManager;
        std::shared_ptr<hid::Gui> layout;
        hid::OpenGLRenderer renderer;
        std::unique_ptr<hid::Scene> scene;
    };
}