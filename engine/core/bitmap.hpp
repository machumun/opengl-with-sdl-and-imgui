#pragma once

#include "internal-ptr.hpp"
#include "sdl-wrapper.hpp"

namespace hid
{
    struct Bitmap
    {
        Bitmap(SDL_Surface *surface);

        uint16_t getWidth() const;
        uint16_t getHeight() const;
        void *getPixelData() const;

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
}