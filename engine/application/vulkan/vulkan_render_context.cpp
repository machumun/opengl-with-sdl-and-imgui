#include "vulkan_render_context.hpp"
#include "vulkan_image_view.hpp"

using hid::VulkanRenderContext;

namespace
{
  hid::VulkanImage createMultiSampleImage(
      const hid::VulkanCommandPool &commandPool,
      const hid::VulkanPhysicalDevice &physicalDevice,
      const hid::VulkanDevice &device,
      const hid::VulkanSwapchain &swapchain)
  {
    const vk::Extent2D &extent{swapchain.getExtent()};

    return hid::VulkanImage{
        commandPool,
        physicalDevice,
        device,
        extent.width,
        extent.height,
        1,
        physicalDevice.getMultiSamplingLevel(),
        swapchain.getColorFormat(),
        vk::ImageTiling::eOptimal,
        vk::ImageUsageFlagBits::eTransientAttachment | vk::ImageUsageFlagBits::eColorAttachment,
        vk::MemoryPropertyFlagBits::eDeviceLocal,
        vk::ImageLayout::eUndefined,
        vk::ImageLayout::eColorAttachmentOptimal};
  }

  hid::VulkanImageView createImageView(const hid::VulkanDevice &device,
                                       const hid::VulkanImage &image,
                                       const vk::ImageAspectFlags &aspectFlags)
  {
    return hid::VulkanImageView(device.getDevice(),
                                image.getImage(),
                                image.getFormat(),
                                aspectFlags,
                                image.getMipLevels());
  }

  hid::VulkanImage createDepthImage(const hid::VulkanCommandPool &commandPool,
                                    const hid::VulkanPhysicalDevice &physicalDevice,
                                    const hid::VulkanDevice &device,
                                    const hid::VulkanSwapchain &swapchain)
  {
    const vk::Extent2D &extent{swapchain.getExtent()};

    return hid::VulkanImage(
        commandPool,
        physicalDevice,
        device,
        extent.width,
        extent.height,
        1,
        physicalDevice.getMultiSamplingLevel(),
        physicalDevice.getDepthFormat(),
        vk::ImageTiling::eOptimal,
        vk::ImageUsageFlagBits::eDepthStencilAttachment,
        vk::MemoryPropertyFlagBits::eDeviceLocal,
        vk::ImageLayout::eUndefined,
        vk::ImageLayout::eDepthStencilAttachmentOptimal);
  }

  std::vector<vk::UniqueFramebuffer> createFramebuffers(const hid::VulkanDevice &device,
                                                        const hid::VulkanSwapchain &swapchain,
                                                        const hid::VulkanRenderPass &renderPass,
                                                        const hid::VulkanImageView &multiSampleImageView,
                                                        const hid::VulkanImageView &depthImageView)
  {
    std::vector<vk::UniqueFramebuffer> framebuffers;

    const vk::Extent2D &extent{swapchain.getExtent()};

    for (const auto &swapchainImageView : swapchain.getImageViews())
    {
      std::array<vk::ImageView, 3> attachments{
          multiSampleImageView.getImageView(),
          depthImageView.getImageView(),
          swapchainImageView->getImageView()};

      vk::FramebufferCreateInfo info{
          vk::FramebufferCreateFlags(),              // Flags
          renderPass.getRenderPass(),                // Render pass
          static_cast<uint32_t>(attachments.size()), // Attachment count
          attachments.data(),                        // Attachments
          extent.width,                              // Width
          extent.height,                             // Height
          1};                                        // Layers

      framebuffers.push_back(device.getDevice().createFramebufferUnique(info));
    }

    return framebuffers;
  }

  vk::Rect2D createScissor(const hid::VulkanSwapchain &swapchain)
  {
    vk::Offset2D offset{0, 0};

    return vk::Rect2D{
        offset,
        swapchain.getExtent()};
  }

  vk::Viewport createViewport(const hid::VulkanSwapchain &swapchain)
  {
    const vk::Extent2D extent{swapchain.getExtent()};
    const float viewportWidth{static_cast<float>(extent.width)};
    const float viewportHeight{static_cast<float>(extent.height)};

    return vk::Viewport{
        0.0f,           // X
        0.0f,           // Y
        viewportWidth,  // Width
        viewportHeight, // Height
        0.0f,           // Min depth
        1.0f};          // Max depth
  }

  std::array<vk::ClearValue, 2> createClearValues()
  {
    vk::ClearValue color;
    color.color = vk::ClearColorValue(std::array<float, 4>{
        164.0f / 256.0f, // Red
        30.0f / 256.0f,  // Green
        34.0f / 256.0f,  // Blue
        1.0f});          // Alpha

    vk::ClearValue depth;
    depth.depthStencil = vk::ClearDepthStencilValue{1.0f, 0};

    return std::array<vk::ClearValue, 2>{color, depth};
  }
}

VulkanRenderContext::VulkanRenderContext(
    const hid::SDLWindow &window,
    const hid::VulkanPhysicalDevice &physicalDevice,
    const hid::VulkanDevice &device,
    const hid::VulkanSurface &surface,
    const hid::VulkanCommandPool &commandPool)
    : swapchain{hid::VulkanSwapchain(window, physicalDevice, device, surface)},
      renderPass{hid::VulkanRenderPass(physicalDevice, device, swapchain)},
      multiSampleImage{::createMultiSampleImage(commandPool, physicalDevice, device, swapchain)},
      multiSampleImageView{::createImageView(device,
                                             multiSampleImage,
                                             vk::ImageAspectFlagBits::eColor)},
      depthImage{::createDepthImage(commandPool, physicalDevice, device, swapchain)},
      depthImageView{::createImageView(device, depthImage, vk::ImageAspectFlagBits::eDepth)},
      framebuffers{::createFramebuffers(device,
                                        swapchain,
                                        renderPass,
                                        multiSampleImageView,
                                        depthImageView)},
      graphicsSemaphores{device.createSemaphores(maxRenderFrames)},
      presentationSemaphores{device.createSemaphores(maxRenderFrames)},
      graphicsFences{device.createFences(maxRenderFrames)},
      scissor{::createScissor(swapchain)},
      viewport{::createViewport(swapchain)},
      clearValues{::createClearValues()}
{
}