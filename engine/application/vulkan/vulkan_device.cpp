#include "vulkan_device.hpp"

using hid::VulkanDevice;

namespace
{

    QueueConfig getQueueConfig(const vk::PhysicalDevice &physicalDevice, const vk::SurfaceKHR &surface)
    {
        static const std::string logTag{"hid::VulkanPhysicalDevice::getGraphicsQueueFamilyIndex"};

        // Assign properties to track selection of graphics and presentation queues,
        // initially with an unset marker value.
        constexpr uint32_t unsetQueueIndex{std::numeric_limits<uint32_t>::max()};
        uint32_t graphicsQueueIndex{unsetQueueIndex};
        uint32_t presentationQueueIndex{unsetQueueIndex};

        // Fetch all the queue family properties supported by the physical device.
        std::vector<vk::QueueFamilyProperties> queueFamilies{physicalDevice.getQueueFamilyProperties()};

        // Search through the available queue families, looking for one that supports graphics.
        for (size_t i = 0; i < queueFamilies.size(); i++)
        {
            vk::QueueFamilyProperties properties{queueFamilies[i]};

            // If the current queue family has graphics capability we will evaluate it as a
            // candidate for both the graphics queue and the presentation queue.
            if (properties.queueCount > 0 && properties.queueFlags & vk::QueueFlagBits::eGraphics)
            {
                const uint32_t currentQueueIndex{static_cast<uint32_t>(i)};

                // If we haven't yet chosen an index for the graphics queue (because it is unset),
                // then remember this index as the graphics queue index.
                if (graphicsQueueIndex == unsetQueueIndex)
                {
                    graphicsQueueIndex = currentQueueIndex;
                }

                // We now need to see if the queue index can also behave as a presentation queue and
                // if so, both the graphics and presentation queue indices will be the same, effectively
                // meaning that we will only need to create a single queue and use it for both purposes.
                if (physicalDevice.getSurfaceSupportKHR(currentQueueIndex, surface))
                {
                    graphicsQueueIndex = currentQueueIndex;
                    presentationQueueIndex = currentQueueIndex;

                    // Since we have now discovered a queue index that can do BOTH graphics and presentation
                    // we won't bother looking any further in the loop.
                    break;
                }
            }
        }

        // If we couldn't find any queues that can perform graphics operations we are out.
        if (graphicsQueueIndex == unsetQueueIndex)
        {
            throw std::runtime_error(logTag + ": Could not find a graphics queue.");
        }

        // If we found a graphics queue, but not one that could also do presentation then we
        // need to find a discrete presentation queue to use instead, meaning we will end
        // up with two queues to manage instead of one that can do both.
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

        // Once more we will see if we have a presentation queue or not - this time if
        // we still do not have one then we are out again.
        if (presentationQueueIndex == unsetQueueIndex)
        {
            throw std::runtime_error(logTag + ": Could not find a presentation queue.");
        }

        // At this point we have valid graphics queue and presentation queue indices
        // so we will wrap them up in a result object and return it. Note that we
        // will also record whether the presentation queue is 'discrete' meaning that
        // it is a different queue to the graphics queue.
        return QueueConfig{
            graphicsQueueIndex,
            presentationQueueIndex,
            graphicsQueueIndex != presentationQueueIndex};
    }

    vk::UniqueDevice createDevice(const hid::VulkanPhysicalDevice &physicalDevice,
                                  const QueueConfig &queueConfig)
    {
        const float deviceQueuePriority{1.0f};

        // Hold a list of queue creation objects to use in our logical device,
        // initialising it with the graphics queue configuration.
        std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos{
            vk::DeviceQueueCreateInfo{
                vk::DeviceQueueCreateFlags(),   // Flags
                queueConfig.graphicsQueueIndex, // Queue family index
                1,                              // Queue count
                &deviceQueuePriority            // Queue priority
            }};

        // Add a presentation queue if the presentation queue needs to be
        // discrete from the graphics queue.
        if (queueConfig.hasDiscretePresentationQueue)
        {
            queueCreateInfos.push_back(vk::DeviceQueueCreateInfo{
                vk::DeviceQueueCreateFlags(),       // Flags
                queueConfig.presentationQueueIndex, // Queue family index
                1,                                  // Queue count
                &deviceQueuePriority                // Queue priority
            });
        }

        // We also need to request the swapchain extension be activated as we will need to use a swapchain
        std::vector<const char *> extensionNames{VK_KHR_SWAPCHAIN_EXTENSION_NAME};

        // Take the queue and extension name configurations and form the device creation definition.
        vk::DeviceCreateInfo deviceCreateInfo{
            vk::DeviceCreateFlags(),                        // Flags
            static_cast<uint32_t>(queueCreateInfos.size()), // Queue create info list count
            queueCreateInfos.data(),                        // Queue create info list
            0,                                              // Enabled layer count
            nullptr,                                        // Enabled layer names
            static_cast<uint32_t>(extensionNames.size()),   // Enabled extension count
            extensionNames.data(),                          // Enabled extension names
            nullptr                                         // Physical device features
        };

        // Create a logical device with all the configuration we collated.
        return physicalDevice.getPhysicalDevice().createDeviceUnique(deviceCreateInfo);
    }
}

VulkanDevice::VulkanDevice(const hid::VulkanPhysicalDevice &physicalDevice,
                           const hid::VulkanSurface &surface)
    : queueConfig{::getQueueConfig(physicalDevice.getPhysicalDevice(), surface.getSurface())},
      device{::createDevice(physicalDevice, queueConfig)} {}

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