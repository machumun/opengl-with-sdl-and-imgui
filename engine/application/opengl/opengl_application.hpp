#pragma once

#include "opengl_imgui.hpp"
#include "opengl_asset_manager.hpp"
#include "opengl_renderer.hpp"

#include "../../../main/src/scene_main.hpp"
#include "../application.hpp"

#include "../../core/layout/layout.hpp"

namespace hid
{
    struct OpenGLApplication : public hid::Application
    {

        OpenGLApplication();
        ~OpenGLApplication();
        void update(const float &delta) override;
        void render() override;
        void start() override;
        void setup() override;

        hid::Scene &getScene();

    private:
        SDL_Window *window;
        SDL_GLContext context;

        std::unique_ptr<hid::Scene> scene;
        std::shared_ptr<hid::Layout> layout;
        hid::OpenGLRenderer renderer;
        std::unique_ptr<hid::OpenGLImGui> imgui;
    };
}