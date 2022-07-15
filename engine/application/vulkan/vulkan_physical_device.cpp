#include "vulkan_physical_device.hpp"
#include "../../core/log.hpp"

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
}

VulkanPhysicalDevice::VulkanPhysicalDevice(const vk::Instance &instance)
    : physicaldevice{::createPhysicalDevice(instance)} {}

const vk::PhysicalDevice &VulkanPhysicalDevice::getPhysicalDevice() const
{
    return physicaldevice;
}