#pragma once

#include "../../core/internal-ptr.hpp"
#include "../../core/sdl-wrapper.hpp"

#include <functional>

namespace hid
{
    struct OpenGLImGui
    {
        OpenGLImGui();
        void setup(SDL_Window *, SDL_GLContext);
        void loop(SDL_Window *);
        void cleanUp();
        void render();

        void setUserImGui(std::function<void()>);

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
}