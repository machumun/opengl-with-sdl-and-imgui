#pragma once

#include "opengl_imgui.hpp"
#include "opengl_asset_manager.hpp"
#include "opengl_renderer.hpp"

#include "../../../main/src/scene_main.hpp"
#include "../application.hpp"

#include "../../core/sdl_window.hpp"

namespace hid
{
    struct OpenGLApplication : public hid::Application
    {

        OpenGLApplication();
        ~OpenGLApplication();
        void update() override;
        void render() override;
        void start() override;
        void setup() override;

    private:
        hid::SDLWindow window;
        SDL_GLContext context;

        std::unique_ptr<hid::OpenGLRenderer> renderer;
        std::unique_ptr<hid::OpenGLImGui> imgui;

        static std::unique_ptr<hid::OpenGLAssetManager> openglAssetManager;
    };
}