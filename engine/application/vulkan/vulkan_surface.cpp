#include "vulkan_surface.hpp"

using hid::VulkanSurface;

namespace
{
    vk::UniqueSurfaceKHR createSurface(const vk::Instance &instance,
                                       const hid::VulkanPhysicalDevice &physicalDevice,
                                       const hid::SDLWindow &window)
    {
        static const std::string logTag{"ast::VulkanSurface::createSurface"};

        VkSurfaceKHR sdlSurface;

        if (!SDL_Vulkan_CreateSurface(window.getWindow(), instance, &sdlSurface))
        {
            throw std::runtime_error(logTag + ": SDL could not create a Vulkan surface.");
        }

        return vk::UniqueSurfaceKHR{sdlSurface, instance};
    }
}

VulkanSurface::VulkanSurface(const vk::Instance &instance,
                             const hid::VulkanPhysicalDevice &physicalDevice,
                             const hid::SDLWindow &window)
    : surface{::createSurface(instance, physicalDevice, window)}
{
}

const vk::SurfaceKHR &VulkanSurface::getSurface() const
{
    return *surface;
}