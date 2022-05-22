#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "platform.hpp"
#include "sdl-wrapper.hpp"

namespace
{
    bool shouldDisplayFullScreen()
    {
        switch (hid::getCurrentPlatform())
        {
        case hid::Platform::ios:
        case hid::Platform::android:
            return true;

        default:
            return false;
        }
    }
} // namespace

std::pair<uint32_t, uint32_t> hid::sdl::getDisplaySize()
{
    uint32_t displayWidth{0};
    uint32_t displayHeight{0};

#ifdef __EMSCRIPTEN__
    displayWidth = static_chid<uint32_t>(EM_ASM_INT({
        return document.getElementById('canvas').width;
    }));

    displayHeight = static_chid<uint32_t>(EM_ASM_INT({
        return document.getElementById('canvas').height;
    }));
#else
    switch (hid::getCurrentPlatform())
    {
    case hid::Platform::ios:
    case hid::Platform::android:
    {
        // For mobile platforms we will fetch the full screen size.
        SDL_DisplayMode displayMode;
        SDL_GetDesktopDisplayMode(0, &displayMode);
        displayWidth = static_cast<uint32_t>(displayMode.w);
        displayHeight = static_cast<uint32_t>(displayMode.h);
        break;
    }

    default:
    {
        // For other platforms we'll just show a fixed size window.
        displayWidth = 1280;
        displayHeight = 800;
        break;
    }
    }
#endif
    return std::make_pair(displayWidth, displayHeight);
}

SDL_Window *hid::sdl::createWindow(const uint32_t &windowFlags)
{
    std::pair<uint32_t, uint32_t> displaySize{hid::sdl::getDisplaySize()};

    SDL_Window *window{SDL_CreateWindow(
        "vulkan with sdl",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        displaySize.first, displaySize.second,
        windowFlags)};

    if (::shouldDisplayFullScreen())
    {
        SDL_SetWindowFullscreen(window, SDL_TRUE);
    }

    return window;
}