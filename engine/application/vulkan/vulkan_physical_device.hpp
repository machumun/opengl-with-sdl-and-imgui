#pragma once

#include "../../core/wrapper/graphics_wrapper.hpp"

namespace hid
{
    struct VulkanPhysicalDevice
    {
        VulkanPhysicalDevice(const vk::Instance &instance);
        const vk::PhysicalDevice &getPhysicalDevice() const;
        vk::Format getDepthFormat() const;
        vk::SampleCountFlagBits getMultiSamplingLevel() const;
        uint32_t getMemoryTypeIndex(const uint32_t &filter, const vk::MemoryPropertyFlags &flags) const;

    private:
        const vk::PhysicalDevice physicalDevice;
        const vk::SampleCountFlagBits multiSamplingLevel;
        const vk::Format depthFormat;
    };
}