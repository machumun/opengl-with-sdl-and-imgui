#pragma once

#include "../../core/wrapper/sdl_wrapper.hpp"

#include <functional>

namespace hid
{
        struct OpenGLImGui
        {
                OpenGLImGui();
                void setup(SDL_Window *, SDL_GLContext);
                void update(SDL_Window *);
                void cleanUp();
                void render();

                void setViewport(std::function<void()>);

        private:
#if defined(IMGUI_IMPL_OPENGL_ES2)
                // GL ES 2.0 + GLSL 100
                const char *glsl_version = "#version 100";
#elif defined(__APPLE__)
                // GL 3.2 Core + GLSL 150
                const char *glsl_version = "#version 150";
#else
                // GL 3.3 + GLSL 330
                const char *glsl_version = "#version 330";
#endif
                std::function<void()> viewport;
        };
}