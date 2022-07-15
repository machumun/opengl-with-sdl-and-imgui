#pragma once

#include "wrapper/sdl_wrapper.hpp"

namespace hid
{

    struct SDLWindow
    {
        SDLWindow(const uint32_t &windowFlags);
        ~SDLWindow()
        {
            SDL_DestroyWindow(window);
        }
        SDL_Window *getWindow() const;

    private:
        SDL_Window *window;
    };
}