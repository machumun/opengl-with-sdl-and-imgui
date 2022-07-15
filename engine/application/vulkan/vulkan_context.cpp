#include "vulkan_context.hpp"
#include "vulkan_common.hpp"

#include "../../core/log.hpp"

#include <string>
#include <vector>
#include <set>

using hid::VulkanContext;

namespace
{
    std::vector<std::string> getDesiredValidationLayers()
    {
        std::vector<std::string> result;

#ifndef NDEBUG
        // If we are in a debug build we will cultivate a list of validation layers.
        static const std::string logTag{"hid::VulkanContext::getDesiredValidationLayers"};

        // Collate which validations layers we are interested in applying if they are available.
        std::set<std::string> desiredLayers{"VK_LAYER_KHRONOS_validation"};

        // Iterate all the available layers for the current device.
        for (auto const &properties : vk::enumerateInstanceLayerProperties())
        {
            std::string layerName = properties.layerName;

            hid::log(logTag, "Available layer: " + layerName);

            // If we are interested in this layer, add it to the result list.
            if (desiredLayers.count(layerName))
            {
                hid::log(logTag, "*** Found desired layer: " + layerName);
                result.push_back(layerName);
            }
        }
#endif

        return result;
    }
    vk::UniqueInstance createInstance()
    {
        static const std::string logTag{"::createInstance"};

        vk::ApplicationInfo applicationInfo{
            "Vulkan Engine",           // application name
            VK_MAKE_VERSION(1, 0, 0),  // application version
            "Vulkan Engine",           // engine name
            VK_MAKE_VERSION(1, 0, 0),  // engine version
            VK_MAKE_VERSION(1, 0, 0)}; // vulkan api version

        std::vector<std::string> requiredExtensionNames{
            hid::vulkan::getRequiredVulkanExtensionNames()};

        std::vector<const char *> extensionNames;
        for (const auto &extension : requiredExtensionNames)
        {

            extensionNames.emplace_back(extension.c_str());
        }

        hid::log(logTag, "Get desired validation layer...");
        std::vector<std::string> desiredValidationLayers{::getDesiredValidationLayers()};
        std::vector<const char *> validationLayers;

        for (const auto &layer : desiredValidationLayers)
        {
            validationLayers.emplace_back(layer.c_str());
        }

        vk::InstanceCreateInfo instanceCreateInfo{
            vk::InstanceCreateFlags(),
            &applicationInfo,
            static_cast<uint32_t>(validationLayers.size()),
            validationLayers.data(),
            static_cast<uint32_t>(extensionNames.size()),
            extensionNames.data()};

        return vk::createInstanceUnique(instanceCreateInfo);
    }
}

VulkanContext::VulkanContext()
    : instance{::createInstance()},
    window{hid::SDLWindow(SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI)},
    physicalDevice{hid::VulkanPhysicalDevice(*instance)}
{
    static const std::string logTag{"hid::VulkanContext"};
    hid::log(logTag, "Initialized Vulkan context successfully.");
}