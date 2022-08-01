#include "vulkan_common.hpp"
#include "../../core/wrapper/graphics_wrapper.hpp"
#include "../../core/wrapper/sdl_wrapper.hpp"
#include "../../core/log.hpp"

#include <memory>
#include <set>

std::vector<std::string> hid::vulkan::getRequiredVulkanExtensionNames()
{
    uint32_t extensionCount;
    SDL_Vulkan_GetInstanceExtensions(nullptr, &extensionCount, nullptr);

    auto extensionNames{std::make_unique<const char **>(new const char *[extensionCount])};
    SDL_Vulkan_GetInstanceExtensions(nullptr, &extensionCount, *extensionNames);
    std::vector<std::string> result(*extensionNames, *extensionNames + extensionCount);

    return result;
}

bool hid::vulkan::isVulkanAvailable()
{
    static const std::string logTag{"ast::vulkan::isVulkanAvailable"};

    if (SDL_Vulkan_LoadLibrary(nullptr) != 0)
    {
        hid::log(logTag, "No SDL Vulkan support found.");
        return false;
    }

    std::vector<std::string> requiredExtensionNamesSource{
        hid::vulkan::getRequiredVulkanExtensionNames()};

    std::set<std::string> requiredExtensionNames(
        requiredExtensionNamesSource.begin(),
        requiredExtensionNamesSource.end());

    if (requiredExtensionNames.empty())
    {
        hid::log(logTag, "No Vulkan required extensions found.");
        return false;
    }

    for (auto const &availableExtension : vk::enumerateInstanceExtensionProperties())
    {
        requiredExtensionNames.erase(availableExtension.extensionName);
    }

    if (!requiredExtensionNames.empty())
    {
        hid::log(logTag, "Missing one or more required Vulkan extensions.");
        return false;
    }

    hid::log(logTag, "Vulkan is available.");
    return true;
}