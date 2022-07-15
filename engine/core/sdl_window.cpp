#include "sdl_window.hpp"

using hid::SDLWindow;

SDLWindow::SDLWindow(const uint32_t &windowFlags)
    : window{hid::sdl::createWindow(windowFlags)}
{
}

SDL_Window *SDLWindow::getWindow() const
{
    return window;
}