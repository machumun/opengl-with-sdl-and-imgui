#pragma once

#include "../../core/wrapper/graphics_wrapper.hpp"
#include "vulkan_physical_device.hpp"
#include "vulkan_surface.hpp"

namespace
{
    struct QueueConfig
    {
        uint32_t graphicsQueueIndex;
        uint32_t presentationQueueIndex;
        bool hasDiscretePresentationQueue;
    };
}

namespace hid
{
    struct VulkanDevice
    {
        VulkanDevice(const hid::VulkanPhysicalDevice &physicalDevice,
                     const hid::VulkanSurface &surface);

        const vk::Device &getDevice() const;

        uint32_t getGraphicsQueueIndex() const;
        uint32_t getPresentationQueueIndex() const;
        bool hasDiscretePresentationQueue() const;

    private:
        const QueueConfig queueConfig;
        const vk::UniqueDevice device;
    };
}