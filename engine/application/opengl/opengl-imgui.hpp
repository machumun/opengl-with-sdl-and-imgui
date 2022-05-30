#pragma once

#include "../../core/internal-ptr.hpp"
#include "../../core/sdl-wrapper.hpp"

#include <functional>

namespace hid
{
    struct OpenGLGui
    {
        OpenGLGui(SDL_Window *window, SDL_GLContext context);
        void setup(SDL_Window *, SDL_GLContext);
        void loopImGui(SDL_Window *);
        void cleanUpImGui();
        void render();


        void setUserImGui(std::function<void()>);

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
}