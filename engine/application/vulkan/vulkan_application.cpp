#include "vulkan_application.hpp"

using hid::VulkanApplication;

VulkanApplication::VulkanApplication() : context{hid::VulkanContext()},
                                         window{hid::sdl::createWindow(SDL_WINDOW_VULKAN |
                                                                       SDL_WINDOW_RESIZABLE |
                                                                       SDL_WINDOW_ALLOW_HIGHDPI)} {}

void VulkanApplication::update() {}

void VulkanApplication::render() {}

void VulkanApplication::start() {}

void VulkanApplication::setup() {}