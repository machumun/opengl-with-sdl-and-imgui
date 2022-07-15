#pragma once

#include "../../core/wrapper/graphics_wrapper.hpp"
#include "../../core/sdl_window.hpp"
#include "vulkan_physical_device.hpp"

namespace hid
{
    struct VulkanSurface
    {
        VulkanSurface(const vk::Instance &instance,
                      const hid::VulkanPhysicalDevice &physicalDevice,
                      const hid::SDLWindow &window);

        const vk::SurfaceKHR &getSurface() const;

    private:
        vk::UniqueSurfaceKHR surface;
    };
}