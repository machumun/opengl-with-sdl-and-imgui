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
        const vk::Queue &getGraphicsQueue() const;
        const vk::Queue &getPresentationQueue() const;

        uint32_t getGraphicsQueueIndex() const;
        uint32_t getPresentationQueueIndex() const;
        bool hasDiscretePresentationQueue() const;

        std::vector<vk::UniqueSemaphore> createSemaphores(const uint32_t &count) const;
        std::vector<vk::UniqueFence> createFences(const uint32_t &count) const;
        vk::UniqueShaderModule VulkanDevice::createShaderModule(const std::vector<char> &shaderCode) const;

    private:
        const QueueConfig queueConfig;
        const vk::UniqueDevice device;
        const vk::Queue graphicsQueue;
        const vk::Queue presentationQueue;
    };
}