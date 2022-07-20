#pragma once

#include "vulkan_device.hpp"
#include "vulkan_physical_device.hpp"
#include "vulkan_surface.hpp"
#include "vulkan_image_view.hpp"

#include <vector>
#include <memory>

#include "../../core/wrapper/graphics_wrapper.hpp"
#include "../../core/sdl_window.hpp"

namespace
{
    struct VulkanSwapchainFormat
    {
        vk::ColorSpaceKHR colorSpace;
        vk::Format colorFormat;
    };
}

namespace hid
{
    struct VulkanSwapchain
    {
        VulkanSwapchain(const hid::SDLWindow &window,
                        const hid::VulkanPhysicalDevice &physicalDevice,
                        const hid::VulkanDevice &device,
                        const hid::VulkanSurface &surface);

        const vk::SwapchainKHR &getSwapchain() const;
        const std::vector<std::unique_ptr<hid::VulkanImageView>> &getImageViews() const;

    private:
        const VulkanSwapchainFormat format;
        const vk::PresentModeKHR presentationMode;
        const vk::Extent2D extent;
        const vk::SurfaceTransformFlagBitsKHR transform;
        const vk::UniqueSwapchainKHR swapchain;
        const std::vector<std::unique_ptr<hid::VulkanImageView>> imageViews;
    };
}