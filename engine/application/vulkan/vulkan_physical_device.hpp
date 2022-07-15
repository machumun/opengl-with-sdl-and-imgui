#pragma once

#include "../../core/wrapper/graphics_wrapper.hpp"

namespace hid
{
    struct VulkanPhysicalDevice
    {
        VulkanPhysicalDevice(const vk::Instance &instance);
        const vk::PhysicalDevice &getPhysicalDevice() const;

    private:
        const vk::PhysicalDevice physicaldevice;
    };
}