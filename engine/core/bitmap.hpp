#pragma once

#include "internal-ptr.hpp"
#include "sdl-wrapper.hpp"

namespace hid
{
    struct Bitmap
    {
        SDL_Surface *surface;
        Bitmap(SDL_Surface *surface) : surface(surface) {}

        ~Bitmap()
        {
            SDL_FreeSurface(surface);
        }

        uint16_t getWidth() const
        {
            return static_cast<uint16_t>(surface->w);
        }

        uint16_t getHeight() const
        {
            return static_cast<uint16_t>(surface->h);
        }

        void *getPixelData() const
        {
            return surface->pixels;
        }
    };
}