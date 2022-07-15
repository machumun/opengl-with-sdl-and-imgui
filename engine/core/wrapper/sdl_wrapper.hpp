#pragma once

#include <SDL.h>
#include <SDL_vulkan.h>
#include <utility>

namespace hid::sdl
{
    std::pair<uint32_t, uint32_t> getDisplaySize();
    SDL_Window *createWindow(const uint32_t &windowFlags);
}