#pragma once

#include "vulkan_physical_device.hpp"
#include "vulkan_surface.hpp"
#include "vulkan_device.hpp"

#include "../../core/sdl_window.hpp"
#include "../../core/wrapper/graphics_wrapper.hpp"


namespace hid
{
    struct VulkanContext
    {
        VulkanContext();

    private:
        const vk::UniqueInstance instance;
        const VulkanPhysicalDevice physicalDevice;
        const hid::SDLWindow window;
        const hid::VulkanSurface surface;
        const hid::VulkanDevice device;
    };
}