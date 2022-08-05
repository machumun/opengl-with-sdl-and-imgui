#include "vulkan_device.hpp"

// #include "../../core/log.hpp"

#include <iostream>

using hid::VulkanDevice;

namespace
{

    QueueConfig getQueueConfig(const vk::PhysicalDevice &physicalDevice, const vk::SurfaceKHR &surface)
    {
        static const std::string logTag{"hid::VulkanPhysicalDevice::getGraphicsQueueFamilyIndex"};

        constexpr uint32_t unsetQueueIndex{std::numeric_limits<uint32_t>::max()};
        uint32_t graphicsQueueIndex{unsetQueueIndex};
        uint32_t presentationQueueIndex{unsetQueueIndex};

        std::vector<vk::QueueFamilyProperties> queueFamilies{physicalDevice.getQueueFamilyProperties()};

        for (size_t i = 0; i < queueFamilies.size(); i++)
        {
            vk::QueueFamilyProperties properties{queueFamilies[i]};

            // hid::log(logTag, "queue family index: " + std::to_string(i));
            // hid::log(logTag, "queue count: " + std::to_string(properties.queueCount);
            // hid::log(logTag, "graphic support: " + (properties.queueFlags & vk::QueueFlagBits::eGraphics ? "True" : "False"));
            // hid::log(logTag, "compute support: " + std::to_string(i));
            // hid::log(logTag, "transfer support: " + std::to_string(i));

            std::cout << "queue family index: " << i << std::endl;
            std::cout << "  queue count: " << properties.queueCount << std::endl;
            std::cout << "  graphic support: " << (properties.queueFlags & vk::QueueFlagBits::eGraphics ? "True" : "False") << std::endl;
            std::cout << "  compute support: " << (properties.queueFlags & vk::QueueFlagBits::eCompute ? "True" : "False") << std::endl;
            std::cout << "  transfer support: " << (properties.queueFlags & vk::QueueFlagBits::eTransfer ? "True" : "False") << std::endl;
            std::cout << std::endl;

            if (properties.queueCount > 0 && properties.queueFlags & vk::QueueFlagBits::eGraphics)
            {
                const uint32_t currentQueueIndex{static_cast<uint32_t>(i)};

                if (graphicsQueueIndex == unsetQueueIndex)
                {
                    graphicsQueueIndex = currentQueueIndex;
                }

                if (physicalDevice.getSurfaceSupportKHR(currentQueueIndex, surface))
                {
                    graphicsQueueIndex = currentQueueIndex;
                    presentationQueueIndex = currentQueueIndex;

                    break;
                }
            }
        }

        if (graphicsQueueIndex == unsetQueueIndex)
        {
            throw std::runtime_error(logTag + ": Could not find a graphics queue.");
        }

        if (presentationQueueIndex == unsetQueueIndex)
        {
            for (size_t i = 0; i < queueFamilies.size(); i++)
            {
                const uint32_t currentQueueIndex{static_cast<uint32_t>(i)};

                if (physicalDevice.getSurfaceSupportKHR(currentQueueIndex, surface))
                {
                    presentationQueueIndex = currentQueueIndex;
                    break;
                }
            }
        }

        if (presentationQueueIndex == unsetQueueIndex)
        {
            throw std::runtime_error(logTag + ": Could not find a presentation queue.");
        }

        return QueueConfig{
            graphicsQueueIndex,
            presentationQueueIndex,
            graphicsQueueIndex != presentationQueueIndex};
    }

    vk::UniqueDevice createDevice(const hid::VulkanPhysicalDevice &physicalDevice,
                                  const QueueConfig &queueConfig)
    {
        const float deviceQueuePriority{1.0f};

        std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos{
            vk::DeviceQueueCreateInfo{
                vk::DeviceQueueCreateFlags(),   // Flags
                queueConfig.graphicsQueueIndex, // Queue family index
                1,                              // Queue count
                &deviceQueuePriority            // Queue priority
            }};

        if (queueConfig.hasDiscretePresentationQueue)
        {
            queueCreateInfos.push_back(vk::DeviceQueueCreateInfo{
                vk::DeviceQueueCreateFlags(),       // Flags
                queueConfig.presentationQueueIndex, // Queue family index
                1,                                  // Queue count
                &deviceQueuePriority                // Queue priority
            });
        }

        std::vector<const char *> extensionNames{VK_KHR_SWAPCHAIN_EXTENSION_NAME};

        vk::PhysicalDeviceFeatures physicalDeviceFeatures;

        if (physicalDevice.isShaderMultiSamplingSupported())
        {
            physicalDeviceFeatures.sampleRateShading = true;
        }

        vk::DeviceCreateInfo deviceCreateInfo{
            vk::DeviceCreateFlags(),                        // Flags
            static_cast<uint32_t>(queueCreateInfos.size()), // Queue create info list count
            queueCreateInfos.data(),                        // Queue create info list
            0,                                              // Enabled layer count
            nullptr,                                        // Enabled layer names
            static_cast<uint32_t>(extensionNames.size()),   // Enabled extension count
            extensionNames.data(),                          // Enabled extension names
            &physicalDeviceFeatures                         // Physical device features
        };

        return physicalDevice.getPhysicalDevice().createDeviceUnique(deviceCreateInfo);
    }

    vk::Queue getQueue(const vk::Device &device, const uint32_t &queueIndex)
    {
        return device.getQueue(queueIndex, 0);
    }

    std::vector<vk::UniqueSemaphore> createSemaphores(const vk::Device &device,
                                                      const uint32_t &count)
    {
        std::vector<vk::UniqueSemaphore> semaphores;
        vk::SemaphoreCreateInfo info;

        for (uint32_t i = 0; i < count; i++)
        {
            semaphores.push_back(device.createSemaphoreUnique(info));
        }

        return semaphores;
    }

    std::vector<vk::UniqueFence> createFences(const vk::Device &device, const uint32_t &count)
    {
        std::vector<vk::UniqueFence> fences;
        vk::FenceCreateInfo info{vk::FenceCreateFlagBits::eSignaled};

        for (uint32_t i = 0; i < count; i++)
        {
            fences.emplace_back(device.createFenceUnique(info));
        }

        return fences;
    }

    vk::UniqueShaderModule createShaderModule(const vk::Device &device, const std::vector<char> &shaderCode)
    {
        vk::ShaderModuleCreateInfo info{
            vk::ShaderModuleCreateFlags(),
            shaderCode.size(),
            reinterpret_cast<const uint32_t *>(shaderCode.data())};

        return device.createShaderModuleUnique(info);
    }
}

VulkanDevice::VulkanDevice(const hid::VulkanPhysicalDevice &physicalDevice,
                           const hid::VulkanSurface &surface)
    : queueConfig{::getQueueConfig(physicalDevice.getPhysicalDevice(), surface.getSurface())},
      device{::createDevice(physicalDevice, queueConfig)},
      graphicsQueue{::getQueue(device.get(), queueConfig.graphicsQueueIndex)},
      presentationQueue{::getQueue(device.get(), queueConfig.presentationQueueIndex)} {}

const vk::Device &VulkanDevice::getDevice() const
{
    return *device;
}

uint32_t VulkanDevice::getGraphicsQueueIndex() const
{
    return queueConfig.graphicsQueueIndex;
}

uint32_t VulkanDevice::getPresentationQueueIndex() const
{
    return queueConfig.presentationQueueIndex;
}

bool VulkanDevice::hasDiscretePresentationQueue() const
{
    return queueConfig.hasDiscretePresentationQueue;
}

const vk::Queue &VulkanDevice::getGraphicsQueue() const
{
    return graphicsQueue;
}

std::vector<vk::UniqueSemaphore> VulkanDevice::createSemaphores(const uint32_t &count) const
{
    return ::createSemaphores(device.get(), count);
}

std::vector<vk::UniqueFence> VulkanDevice::createFences(const uint32_t &count) const
{
    return ::createFences(device.get(), count);
}

const vk::Queue &VulkanDevice::getPresentationQueue() const
{
    return presentationQueue;
}

vk::UniqueShaderModule VulkanDevice::createShaderModule(const std::vector<char> &shaderCode) const
{
    return ::createShaderModule(device.get(), shaderCode);
}