#include "vulkan_swapchain.hpp"

#include "../../core/log.hpp"

#include <stack>

using hid::VulkanSwapchain;

namespace
{
    VulkanSwapchainFormat getFormat(const hid::VulkanPhysicalDevice &physicalDevice,
                                    const hid::VulkanSurface &surface)
    {
        static const std::string logTag{"hid::VulkanSwapchain::getFormat"};

        // We need to make sure that there is at least one surface format compatible with our surface.
        std::vector<vk::SurfaceFormatKHR> availableSurfaceFormats{
            physicalDevice.getPhysicalDevice().getSurfaceFormatsKHR(surface.getSurface())};

        size_t availableFormatCount{availableSurfaceFormats.size()};

        if (availableFormatCount == 0)
        {
            throw std::runtime_error(logTag + ": No compatible surface formats found.");
        }

        // Take the first format as a 'default'.
        vk::SurfaceFormatKHR defaultFormat{availableSurfaceFormats[0]};

        // If there is only one surface with an undefined format, we will manually choose one.
        if (availableFormatCount == 1 && defaultFormat.format == vk::Format::eUndefined)
        {
            hid::log(logTag, "Surface format is undefined: defaulting to eSrgbNonlinear + eR8G8B8Unorm.");
            return VulkanSwapchainFormat{vk::ColorSpaceKHR::eSrgbNonlinear, vk::Format::eR8G8B8Unorm};
        }

        // We will look through the available formats, attempting to prefer the eR8G8B8Unorm type.
        for (const auto &availableFormat : availableSurfaceFormats)
        {
            if (availableFormat.format == vk::Format::eR8G8B8Unorm)
            {
                hid::log(logTag, "Found supported eR8G8B8Unorm surface format.");
                return VulkanSwapchainFormat{availableFormat.colorSpace, availableFormat.format};
            }
        }

        // Otherwise we will just have to use the first available format.
        hid::log(logTag, "Surface format eR8G8B8Unorm not found, using default available format.");
        return VulkanSwapchainFormat{defaultFormat.colorSpace, defaultFormat.format};
    }

    vk::PresentModeKHR getPresentationMode(const hid::VulkanPhysicalDevice &physicalDevice,
                                           const hid::VulkanSurface &surface)
    {
        static const std::string logTag{"hid::VulkanSwapchain::getPresentationMode"};

        // We need to make sure that there is at least one presentation mode compatible with our surface.
        std::vector<vk::PresentModeKHR> availableModes{
            physicalDevice.getPhysicalDevice().getSurfacePresentModesKHR(surface.getSurface())};

        if (availableModes.empty())
        {
            throw std::runtime_error(logTag + ": No compatible present modes found.");
        }

        // Load up the presentation modes into a stack so they are popped
        // in our preferred order for evaluation.
        std::stack<vk::PresentModeKHR> preferredModes;
        preferredModes.push(vk::PresentModeKHR::eImmediate);
        preferredModes.push(vk::PresentModeKHR::eFifoRelaxed);
        preferredModes.push(vk::PresentModeKHR::eFifo);
        preferredModes.push(vk::PresentModeKHR::eMailbox);

        while (!preferredModes.empty())
        {
            // Take the mode at the top of the stack and see if the list of available modes contains it.
            vk::PresentModeKHR mode{preferredModes.top()};

            if (std::find(availableModes.begin(), availableModes.end(), mode) != availableModes.end())
            {
                // If we find the current preferred presentation mode, we are done.
                return mode;
            }

            // If our preferred mode is not found, pop the stack ready for the next iteration.
            preferredModes.pop();
        }

        // None of our preferred presentation modes were found, can't go further...
        throw std::runtime_error(logTag + ": No compatible presentation modes found.");
    }

    vk::Extent2D getExtent(const hid::SDLWindow &window)
    {
        int drawableWidth;
        int drawableHeight;
        SDL_Vulkan_GetDrawableSize(window.getWindow(), &drawableWidth, &drawableHeight);

        return vk::Extent2D{
            static_cast<uint32_t>(drawableWidth),
            static_cast<uint32_t>(drawableHeight)};
    }

    vk::UniqueSwapchainKHR createSwapchain(
        const hid::VulkanPhysicalDevice &physicalDevice,
        const hid::VulkanDevice &device,
        const hid::VulkanSurface &surface,
        const VulkanSwapchainFormat &format,
        const vk::PresentModeKHR &presentationMode,
        const vk::Extent2D &extent,
        const vk::SurfaceTransformFlagBitsKHR &transform,
        const vk::SwapchainKHR &oldSwapchain)
    {
        // Grab the capabilities of the current physical device in relation to the surface.
        vk::SurfaceCapabilitiesKHR surfaceCapabilities{
            physicalDevice.getPhysicalDevice().getSurfaceCapabilitiesKHR(surface.getSurface())};

        // We will pick a minimum image count of +1 to the minimum supported on the device.
        uint32_t minimumImageCount{surfaceCapabilities.minImageCount + 1};
        uint32_t maxImageCount{surfaceCapabilities.maxImageCount};

        // Make sure our image count doesn't exceed any maximum if there is one.
        // Note: The Vulkan docs state that a value of 0 doesn't mean there is
        // a limit of 0, it means there there is no limit.
        if (maxImageCount > 0 && minimumImageCount > maxImageCount)
        {
            minimumImageCount = maxImageCount;
        }

        vk::SwapchainCreateInfoKHR createInfo{
            vk::SwapchainCreateFlagsKHR(),            // Flags
            surface.getSurface(),                     // Surface
            minimumImageCount,                        // Minimum image count
            format.colorFormat,                       // Image format
            format.colorSpace,                        // Image color space
            extent,                                   // Image extent
            1,                                        // Image array layers
            vk::ImageUsageFlagBits::eColorAttachment, // Image usage
            vk::SharingMode::eExclusive,              // Image sharing mode
            0,                                        // Queue family index count
            nullptr,                                  // Queue family indices
            transform,                                // Pre transform
            vk::CompositeAlphaFlagBitsKHR::eOpaque,   // Composite alpha
            presentationMode,                         // Present mode
            VK_TRUE,                                  // Clipped
            oldSwapchain};                            // Old swapchain

        // If our device has a discrete presentation queue, we must specify
        // that swapchain images are permitted to be shared between both
        // the graphics and presentation queues.
        if (device.hasDiscretePresentationQueue())
        {
            std::array<uint32_t, 2> queueIndices{
                device.getGraphicsQueueIndex(),
                device.getPresentationQueueIndex()};

            createInfo.imageSharingMode = vk::SharingMode::eConcurrent;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueIndices.data();
        }

        return device.getDevice().createSwapchainKHRUnique(createInfo);
    }

    std::vector<std::unique_ptr<hid::VulkanImageView>> createImageViews(const hid::VulkanDevice &device,
                                                                        const vk::SwapchainKHR &swapChain,
                                                                        const VulkanSwapchainFormat &format)
    {
        std::vector<std::unique_ptr<hid::VulkanImageView>> imageViews;

        // For each of the images in the swap chain, we need to create a new 'image view'.
        for (const vk::Image &image : device.getDevice().getSwapchainImagesKHR(swapChain))
        {
            std::unique_ptr<hid::VulkanImageView> imageView = std::make_unique<hid::VulkanImageView>(
                device.getDevice(),
                image,
                format.colorFormat,
                vk::ImageAspectFlagBits::eColor,
                1);

            imageViews.emplace_back(std::move(imageView));
        }

        return imageViews;
    }

}

VulkanSwapchain::VulkanSwapchain(const hid::SDLWindow &window,
                                 const hid::VulkanPhysicalDevice &physicalDevice,
                                 const hid::VulkanDevice &device,
                                 const hid::VulkanSurface &surface,
                                 const vk::SwapchainKHR &oldSwapchain)
    : format{::getFormat(physicalDevice, surface)},
      presentationMode{::getPresentationMode(physicalDevice, surface)},
      extent{::getExtent(window)},
      transform{vk::SurfaceTransformFlagBitsKHR::eIdentity},
      swapchain{::createSwapchain(physicalDevice,
                                  device,
                                  surface,
                                  format,
                                  presentationMode,
                                  extent,
                                  transform,
                                  oldSwapchain)},
      imageViews{::createImageViews(device, swapchain.get(), format)}
{
}

const vk::SwapchainKHR &VulkanSwapchain::getSwapchain() const
{
    return swapchain.get();
}

const std::vector<std::unique_ptr<hid::VulkanImageView>> &VulkanSwapchain::getImageViews() const
{
    return imageViews;
}

const vk::Format &VulkanSwapchain::getColorFormat() const
{
    return format.colorFormat;
}

const vk::Extent2D &VulkanSwapchain::getExtent() const
{
    return extent;
}

uint32_t VulkanSwapchain::getImageCount() const
{
    return static_cast<uint32_t>(imageViews.size());
}