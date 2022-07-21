#pragma once

#include "vulkan_device.hpp"
#include "vulkan_physical_device.hpp"
#include "vulkan_swapchain.hpp"

namespace hid
{
    struct VulkanRenderPass
    {
        VulkanRenderPass(const hid::VulkanPhysicalDevice &physicalDevice,
                         const hid::VulkanDevice &device,
                         const hid::VulkanSwapchain &swapchain);

        const vk::RenderPass &getRenderPass() const;

    private:
        const vk::UniqueRenderPass renderPass;
    };
}