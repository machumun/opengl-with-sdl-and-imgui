#pragma once

#include "../../core/wrapper/graphics_wrapper.hpp"
#include "vulkan_device.hpp"
#include "vulkan_physical_device.hpp"
#include "vulkan_command_pool.hpp"

namespace hid
{
    struct VulkanImage
    {
        VulkanImage(const hid::VulkanCommandPool &commandPool,
                    const hid::VulkanPhysicalDevice &physicalDevice,
                    const hid::VulkanDevice &device,
                    const uint32_t &width,
                    const uint32_t &height,
                    const uint32_t &mipLevels,
                    const vk::SampleCountFlagBits &sampleCount,
                    const vk::Format &format,
                    const vk::ImageTiling &tiling,
                    const vk::ImageUsageFlags &usageFlags,
                    const vk::MemoryPropertyFlags &memoryFlags,
                    const vk::ImageLayout &oldLayout,
                    const vk::ImageLayout &newLayout);

        uint32_t getWidth() const;

        uint32_t getHeight() const;

        uint32_t getMipLevels() const;

        const vk::Format &getFormat() const;

        const vk::Image &getImage() const;

    private:
        const uint32_t width;
        const uint32_t height;
        const uint32_t mipLevels;
        const vk::Format format;
        const vk::UniqueImage image;
        const vk::UniqueDeviceMemory imageMemory;
    };
}