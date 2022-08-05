#pragma once

#include "../../core/sdl_window.hpp"
#include "vulkan_device.hpp"
#include "vulkan_physical_device.hpp"
#include "vulkan_surface.hpp"
#include "vulkan_swapchain.hpp"
#include "vulkan_render_pass.hpp"
#include "vulkan_command_pool.hpp"
#include "vulkan_image.hpp"

#include <memory>

namespace hid
{
    struct VulkanRenderContext
    {
        VulkanRenderContext(
            const hid::SDLWindow &window,
            const hid::VulkanPhysicalDevice &physicalDevice,
            const hid::VulkanDevice &device,
            const hid::VulkanSurface &surface,
            const hid::VulkanCommandPool &commandPool,
            const vk::SwapchainKHR &oldSwapchain = vk::SwapchainKHR());

        bool renderBegin(const hid::VulkanDevice &device);

        bool renderEnd(const hid::VulkanDevice &device);

        std::unique_ptr<hid::VulkanRenderContext> recreate(const hid::SDLWindow &window,
                                                           const hid::VulkanPhysicalDevice &physicalDevice,
                                                           const hid::VulkanDevice &device,
                                                           const hid::VulkanSurface &surface,
                                                           const hid::VulkanCommandPool &commandPool);

        const vk::Viewport &getViewport() const;

        const vk::Rect2D &getScissor() const;

        const vk::RenderPass &getRenderPass() const;

    private:
        const hid::VulkanSwapchain swapchain;
        const hid::VulkanRenderPass renderPass;

        const hid::VulkanImage multiSampleImage;
        const hid::VulkanImageView multiSampleImageView;

        const hid::VulkanImage depthImage;
        const hid::VulkanImageView depthImageView;

        const std::vector<vk::UniqueFramebuffer> framebuffers;

        const uint32_t maxRenderFrames{2};

        const std::vector<vk::UniqueCommandBuffer> commandBuffers;

        const std::vector<vk::UniqueSemaphore> graphicsSemaphores;
        const std::vector<vk::UniqueSemaphore> presentationSemaphores;

        const std::vector<vk::UniqueFence> graphicsFences;
        const vk::Rect2D scissor;

        const vk::Viewport viewport;

        const std::array<vk::ClearValue, 2> clearValues;

        uint32_t currentFrameIndex{0};
        uint32_t currentSwapchainImageIndex{0};
    };
}