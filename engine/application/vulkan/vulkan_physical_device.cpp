#include "vulkan_physical_device.hpp"
#include "../../core/log.hpp"

#include <stack>

using hid::VulkanPhysicalDevice;

namespace
{
    vk::PhysicalDevice createPhysicalDevice(const vk::Instance &instance)
    {
        static const std::string logTag{"hid::VulkanPhysicalDevice::createPhysicalDevice"};

        std::vector<vk::PhysicalDevice> devices{instance.enumeratePhysicalDevices()};

        if (devices.empty())
        {
            throw std::runtime_error(logTag + ": No Vulkan physical devices found");
        }

        vk::PhysicalDevice selectedDevice{devices[0]};
        vk::PhysicalDeviceProperties selectedProperties{selectedDevice.getProperties()};

        if (selectedProperties.deviceType != vk::PhysicalDeviceType::eDiscreteGpu)
        {
            for (size_t i = 1; i < devices.size(); i++)
            {
                vk::PhysicalDevice &nextDevice{devices[i]};
                vk::PhysicalDeviceProperties nextProperties{nextDevice.getProperties()};

                // If we find a device with a discrete GPU, then choose it and we are done.
                if (nextProperties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
                {
                    selectedDevice = nextDevice;
                    selectedProperties = nextProperties;
                    break;
                }
            }
        }

        bool hasSwapchainSupport{false};
        std::string swapchainName{VK_KHR_SWAPCHAIN_EXTENSION_NAME};

        for (const auto &extension : selectedDevice.enumerateDeviceExtensionProperties())
        {
            hid::log(logTag, extension.extensionName);
            if (extension.extensionName.data() == swapchainName)
            {
                hasSwapchainSupport = true;
                break;
            }
        }

        if (!hasSwapchainSupport)
        {
            throw std::runtime_error(logTag + ": Swapchain support not found.");
        }

        hid::log(logTag, "Physical device: " + std::string{selectedProperties.deviceName.data()} + ".");

        return selectedDevice;
    }

    vk::SampleCountFlagBits getMultiSamplingLevel(const vk::PhysicalDevice &physicalDevice)
    {
        static const std::string logTag{"hid::VulkanPhysicalDevice::getMultiSamplingLevel"};

        vk::PhysicalDeviceProperties properties{physicalDevice.getProperties()};
        vk::SampleCountFlags supportedSampleCounts{properties.limits.framebufferColorSampleCounts};

        std::stack<vk::SampleCountFlagBits> preferredSampleCounts;
        preferredSampleCounts.push(vk::SampleCountFlagBits::e1);
        preferredSampleCounts.push(vk::SampleCountFlagBits::e2);
        preferredSampleCounts.push(vk::SampleCountFlagBits::e4);
        preferredSampleCounts.push(vk::SampleCountFlagBits::e8);

        while (!preferredSampleCounts.empty())
        {
            // Take the sample count at the top of the stack and see if it is supported.
            vk::SampleCountFlagBits sampleCount{preferredSampleCounts.top()};

            if (supportedSampleCounts & sampleCount)
            {
                return sampleCount;
            }

            // If our preferred sample count is not found, pop the stack ready for the next iteration.
            preferredSampleCounts.pop();
        }

        // If none of our sample counts is found, multi sampling is not supported on this device ...
        throw std::runtime_error(logTag + ": Multi sampling not supported.");
    }

    vk::Format getDepthFormat(const vk::PhysicalDevice &physicalDevice)
    {
        static const std::string logTag{"hid::VulkanPhysicalDevice::getDepthFormat"};

        vk::FormatProperties formatProperties{physicalDevice.getFormatProperties(vk::Format::eD32Sfloat)};

        if (formatProperties.optimalTilingFeatures & vk::FormatFeatureFlagBits::eDepthStencilAttachment)
        {
            return vk::Format::eD32Sfloat;
        }

        throw std::runtime_error(logTag + ": 32 bit signed depth stencil format not supported.");
    }

    uint32_t getMemoryTypeIndex(const vk::PhysicalDevice &physicalDevice,
                                const uint32_t &filter,
                                const vk::MemoryPropertyFlags &flags)
    {
        // Fetch all the memory properties of the physical device.
        vk::PhysicalDeviceMemoryProperties memoryProperties{physicalDevice.getMemoryProperties()};

        // Loop through each of the memory type fields in the properties.
        for (uint32_t index = 0; index < memoryProperties.memoryTypeCount; index++)
        {
            // If the current memory type is available and has all the property flags required, we
            // have found a position in the physical device memory indices that is compatible.
            if ((filter & (1 << index)) && (memoryProperties.memoryTypes[index].propertyFlags & flags) == flags)
            {
                return index;
            }
        }

        // If no memory type could be found that meets our criteria we can't proceed.
        throw std::runtime_error("ast::VulkanImage::getMemoryTypeIndex: Failed to find suitable memory type.");
    }
}

VulkanPhysicalDevice::VulkanPhysicalDevice(const vk::Instance &instance)
    : physicalDevice{::createPhysicalDevice(instance)},
      multiSamplingLevel{::getMultiSamplingLevel(physicalDevice)},
      depthFormat{::getDepthFormat(physicalDevice)} {}

const vk::PhysicalDevice &VulkanPhysicalDevice::getPhysicalDevice() const
{
    return physicalDevice;
}

vk::Format VulkanPhysicalDevice::getDepthFormat() const
{
    return depthFormat;
}

vk::SampleCountFlagBits VulkanPhysicalDevice::getMultiSamplingLevel() const
{
    return multiSamplingLevel;
}

uint32_t VulkanPhysicalDevice::getMemoryTypeIndex(const uint32_t &filter,
                                                  const vk::MemoryPropertyFlags &flags) const
{
    return ::getMemoryTypeIndex(physicalDevice, filter, flags);
}