#pragma once

// using hid::VulkanCommand

#include "vulkan_device.hpp"

#include <vector>

namespace hid
{
    struct VulkanCommandPool
    {
        VulkanCommandPool(const hid::VulkanDevice &device);
        vk::UniqueCommandBuffer beginCommandBuffer(const hid::VulkanDevice &device) const;

        void endCommandBuffer(const vk::CommandBuffer &commandBuffer,
                              const hid::VulkanDevice &device) const;

        std::vector<vk::UniqueCommandBuffer> createCommandBuffers(const hid::VulkanDevice &device,
                                                                  const uint32_t &count) const;

    private:
        const vk::UniqueCommandPool commandPool;
    };
}